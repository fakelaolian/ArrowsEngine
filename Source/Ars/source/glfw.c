/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
#include "glfw.h"

#include "core.h"
#include <stdlib.h>

ARS_CREATE_WINDOW                  ARSCREATEWIDNOW                      = NULL;
ARS_GET_ASPECT                     ARSGETASPECT                         = NULL;
ARS_WINDOW_SHOULD_CLOSE            ARSWINDOWSHOULDCLOSE                 = NULL;
ARS_WINDOW_SET_RESIZE_CALLBACK     ARSWINDOWSETRESIZECALLBACK           = NULL;
ARS_WINDOW_SET_CURSOR_CALLBACK     ARSWINDOWSETCURSORCALLBACK           = NULL;
ARS_WINDOW_POLL_EVENTS             ARSWINDOWPOLLEVENTS                  = NULL;
ARS_DELETE_WINDOW                  ARSDELETWINDOW                       = NULL;
ARS_TERMINATE                      ARSTERMINATE                         = NULL;
ARS_OPENGL_GET_CURRENT_CONTEXT     ARSOPENGLGETCURRENTCONTEXT           = NULL;
ARS_OPENGL_MAKE_CONTEXT_CURRENT    ARSOPENGLMAKECONTEXTCURRENT          = NULL;
ARS_GET_KEY                        ARSGETKEY                            = NULL;
ARS_GET_MOUSE_BUTTON               ARSGETMOUSEBUTTON                    = NULL;
ARS_SET_CURSOR_INPUT_MODE          ARSSETCURSORINPUTMODE                = NULL;
ARS_SET_USER_POINTER               ARSSETUSERPOINTER                    = NULL;
ARS_GET_USER_POINTER               ARSGETUSERPOINTER                    = NULL;

F_ARS_WINDOW_RESIZE_CALLBACK            _window_resize_callback                  = NULL;
F_ARS_WINDOW_CURSOR_CALLBACK            _window_cursor_callback                  = NULL;

void _glfw_create_window(const char *title, int width, int height, ArsWindow *rhiWindow)
{
        /* 初始化窗口 */
        GLFWwindow *_window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (_window == NULL) {
                verror("创建窗口失败");
                glfwTerminate();
                *rhiWindow = NULL;
                return;
        }

        /* 初始化GLAD */
        glfwMakeContextCurrent(_window);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                glfwDestroyWindow(_window);
                glfwTerminate();

                verror("加载GLAD失败");
                *rhiWindow = NULL;
                return;
        }

        *rhiWindow = _window;
}

arsbool _glfw_should_clsoe(ArsWindow window)
{ return glfwWindowShouldClose((GLFWwindow *) window); }

void _glfw_set_window_resize_callback0(GLFWwindow *window, int x, int y)
{ _window_resize_callback(window, x, y); }

void _glfw_set_window_resize_callback(ArsWindow window, F_ARS_WINDOW_RESIZE_CALLBACK fcallback)
{
        _window_resize_callback = fcallback;
        glfwSetFramebufferSizeCallback((GLFWwindow *) window, _glfw_set_window_resize_callback0);
}

void _glfw_set_window_cursor_callback0(GLFWwindow *window, double x, double y)
{ _window_cursor_callback(window, x, y); }

void _glfw_set_window_cursor_callback(ArsWindow window, F_ARS_WINDOW_CURSOR_CALLBACK fcallback)
{
        _window_cursor_callback = fcallback;
        glfwSetCursorPosCallback((GLFWwindow *) window, _glfw_set_window_cursor_callback0);
}

void _glfw_poll_events()
{ glfwPollEvents(); }

void _glfw_destroy_window(ArsWindow window)
{ glfwDestroyWindow((GLFWwindow *) window); }

void _glfw_terminate()
{ glfwTerminate(); }

ArsWindow _glfw_get_current_context()
{ return glfwGetCurrentContext(); }

void _glfw_make_context_current(ArsWindow h)
{ glfwMakeContextCurrent((GLFWwindow *) h); }

arsbool _glfw_get_key(ArsWindow window, ArsKeyCodeBits keycode)
{ return glfwGetKey((GLFWwindow *) window, keycode); }

void _glfw_set_user_pointer(ArsWindow window, void *any)
{ glfwSetWindowUserPointer(window, any); }

void *_glfw_get_user_pointer(ArsWindow window)
{ return glfwGetWindowUserPointer(window); }

void _glfw_set_cursor_mode(ArsWindow window, ArsInputCursorModeBits bit)
{
        switch (bit) {

                case ARS_CURSOR_NORMAL:  glfwSetInputMode((GLFWwindow *) window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);   break;
                case ARS_CURSOR_HIDDEN:  glfwSetInputMode((GLFWwindow *) window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);   break;
                case ARS_CURSOR_DISABLE: glfwSetInputMode((GLFWwindow *) window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); break;
        }
}

ArsKeyModeBits _glfw_get_mouse_button(ArsWindow window, ArsMouseButtonBits bit)
{ return glfwGetMouseButton(window, bit); }

void _load_glfw_functions()
{
        if(!glfwInit()) {
                verror("ERROR - 初始化GLFW失败");
                exit(1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        ARSCREATEWIDNOW             = _glfw_create_window;
        ARSWINDOWSHOULDCLOSE        = _glfw_should_clsoe;
        ARSWINDOWSETRESIZECALLBACK  = _glfw_set_window_resize_callback;
        ARSWINDOWPOLLEVENTS         = _glfw_poll_events;
        ARSDELETWINDOW              = _glfw_destroy_window;
        ARSTERMINATE                = _glfw_terminate;
        ARSOPENGLGETCURRENTCONTEXT  = _glfw_get_current_context;
        ARSOPENGLMAKECONTEXTCURRENT = _glfw_make_context_current;
        ARSGETKEY                   = _glfw_get_key;
        ARSSETCURSORINPUTMODE       = _glfw_set_cursor_mode;
        ARSSETUSERPOINTER           = _glfw_set_user_pointer;
        ARSGETUSERPOINTER           = _glfw_get_user_pointer;
        ARSWINDOWSETCURSORCALLBACK  = _glfw_set_window_cursor_callback;
        ARSGETMOUSEBUTTON           = _glfw_get_mouse_button;
}