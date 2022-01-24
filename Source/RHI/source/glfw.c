/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
#include "glfw.h"

#include "core.h"
#include <stdlib.h>

ARROWS_RHI_CREATE_WINDOW                  ARROWSRHICREATEWIDNOW                      = NULL;
ARROWS_RHI_GET_ASPECT                     ARROWSRHIGETASPECT                         = NULL;
ARROWS_RHI_WINDOW_SHOULD_CLOSE            ARROWSRHIWINDOWSHOULDCLOSE                 = NULL;
ARROWS_RHI_WINDOW_SET_RESIZE_CALLBACK     ARROWSRHIWINDOWSETRESIZECALLBACK           = NULL;
ARROWS_RHI_WINDOW_SET_CURSOR_CALLBACK     ARROWSRHIWINDOWSETCURSORCALLBACK           = NULL;
ARROWS_RHI_WINDOW_POLL_EVENTS             ARROWSRHIWINDOWPOLLEVENTS                  = NULL;
ARROWS_RHI_DELETE_WINDOW                  ARROWSRHIDELETWINDOW                       = NULL;
ARROWS_RHI_TERMINATE                      ARROWSRHITERMINATE                         = NULL;
ARROWS_RHI_OPENGL_GET_CURRENT_CONTEXT     ARROWSRHIOPENGLGETCURRENTCONTEXT           = NULL;
ARROWS_RHI_OPENGL_MAKE_CONTEXT_CURRENT    ARROWSRHIOPENGLMAKECONTEXTCURRENT          = NULL;
ARROWS_RHI_GET_KEY                        ARROWSRHIGETKEY                            = NULL;
ARROWS_RHI_GET_MOUSE_BUTTON               ARROWSRHIGETMOUSEBUTTON                    = NULL;
ARROWS_RHI_SET_CURSOR_INPUT_MODE          ARROWSRHISETCURSORINPUTMODE                = NULL;
ARROWS_RHI_SET_USER_POINTER               ARROWSRHISETUSERPOINTER                    = NULL;
ARROWS_RHI_GET_USER_POINTER               ARROWSRHIGETUSERPOINTER                    = NULL;

F_RHI_WINDOW_RESIZE_CALLBACK            _window_resize_callback                  = NULL;
F_RHI_WINDOW_CURSOR_CALLBACK            _window_cursor_callback                  = NULL;

void _glfw_create_window(const char *title, int width, int height, RHIWindow *rhiWindow)
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

arrobool _glfw_should_clsoe(RHIWindow window)
{ return glfwWindowShouldClose((GLFWwindow *) window); }

void _glfw_set_window_resize_callback0(GLFWwindow *window, int x, int y)
{ _window_resize_callback(window, x, y); }

void _glfw_set_window_resize_callback(RHIWindow window, F_RHI_WINDOW_RESIZE_CALLBACK fcallback)
{
        _window_resize_callback = fcallback;
        glfwSetFramebufferSizeCallback((GLFWwindow *) window, _glfw_set_window_resize_callback0);
}

void _glfw_set_window_cursor_callback0(GLFWwindow *window, double x, double y)
{ _window_cursor_callback(window, x, y); }

void _glfw_set_window_cursor_callback(RHIWindow window, F_RHI_WINDOW_CURSOR_CALLBACK fcallback)
{
        _window_cursor_callback = fcallback;
        glfwSetCursorPosCallback((GLFWwindow *) window, _glfw_set_window_cursor_callback0);
}

void _glfw_poll_events()
{ glfwPollEvents(); }

void _glfw_destroy_window(RHIWindow window)
{ glfwDestroyWindow((GLFWwindow *) window); }

void _glfw_terminate()
{ glfwTerminate(); }

RHIWindow _glfw_get_current_context()
{ return glfwGetCurrentContext(); }

void _glfw_make_context_current(RHIWindow h)
{ glfwMakeContextCurrent((GLFWwindow *) h); }

arrobool _glfw_get_key(RHIWindow window, RHIKeyCodeBits keycode)
{ return glfwGetKey((GLFWwindow *) window, keycode); }

void _glfw_set_user_pointer(RHIWindow window, void *any)
{ glfwSetWindowUserPointer(window, any); }

void *_glfw_get_user_pointer(RHIWindow window)
{ return glfwGetWindowUserPointer(window); }

void _glfw_set_cursor_mode(RHIWindow window, RHIInputCursorModeBits bit)
{
        switch (bit) {

                case RHI_CURSOR_NORMAL:  glfwSetInputMode((GLFWwindow *) window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);   break;
                case RHI_CURSOR_HIDDEN:  glfwSetInputMode((GLFWwindow *) window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);   break;
                case RHI_CURSOR_DISABLE: glfwSetInputMode((GLFWwindow *) window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); break;
        }
}

RHIKeyModeBits _glfw_get_mouse_button(RHIWindow window, RHIMouseButtonBits bit)
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

        ARROWSRHICREATEWIDNOW             = _glfw_create_window;
        ARROWSRHIWINDOWSHOULDCLOSE        = _glfw_should_clsoe;
        ARROWSRHIWINDOWSETRESIZECALLBACK  = _glfw_set_window_resize_callback;
        ARROWSRHIWINDOWPOLLEVENTS         = _glfw_poll_events;
        ARROWSRHIDELETWINDOW              = _glfw_destroy_window;
        ARROWSRHITERMINATE                = _glfw_terminate;
        ARROWSRHIOPENGLGETCURRENTCONTEXT  = _glfw_get_current_context;
        ARROWSRHIOPENGLMAKECONTEXTCURRENT = _glfw_make_context_current;
        ARROWSRHIGETKEY                   = _glfw_get_key;
        ARROWSRHISETCURSORINPUTMODE       = _glfw_set_cursor_mode;
        ARROWSRHISETUSERPOINTER           = _glfw_set_user_pointer;
        ARROWSRHIGETUSERPOINTER           = _glfw_get_user_pointer;
        ARROWSRHIWINDOWSETCURSORCALLBACK  = _glfw_set_window_cursor_callback;
        ARROWSRHIGETMOUSEBUTTON           = _glfw_get_mouse_button;
}