/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
#include "glfw.h"

#include "core.h"
#include <stdlib.h>

ANCI_RHI_CREATE_WINDOW                  ANCIRHICREATEWIDNOW                      = NULL;
ANCI_RHI_WINDOW_SHOULD_CLOSE            ANCIRHIWINDOWSHOULDCLOSE                 = NULL;
ANCI_RHI_WINDOW_SET_RESIZE_CALLBACK     ANCIRHIWINDOWSETRESIZECALLBACK           = NULL;
ANCI_RHI_WINDOW_SET_CURSOR_CALLBACK     ANCIRHIWINDOWSETCURSORCALLBACK           = NULL;
ANCI_RHI_WINDOW_POLL_EVENTS             ANCIRHIWINDOWPOLLEVENTS                  = NULL;
ANCI_RHI_DELETE_WINDOW                  ANCIRHIDELETWINDOW                       = NULL;
ANCI_RHI_TERMINATE                      ANCIRHITERMINATE                         = NULL;
ANCI_RHI_OPENGL_GET_CURRENT_CONTEXT     ANCIRHIOPENGLGETCURRENTCONTEXT           = NULL;
ANCI_RHI_OPENGL_MAKE_CONTEXT_CURRENT    ANCIRHIOPENGLMAKECONTEXTCURRENT          = NULL;
ANCI_RHI_GET_KEY                        ANCIRHIGETKEY                            = NULL;
ANCI_RHI_SET_CURSOR_INPUT_MODE          ANCIRHISETCURSORINPUTMODE                = NULL;
ANCI_RHI_SET_USER_POINTER               ANCIRHISETUSERPOINTER                    = NULL;
ANCI_RHI_GET_USER_POINTER               ANCIRHIGETUSERPOINTER                    = NULL;

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

ancibool _glfw_should_clsoe(RHIWindow window)
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

ancibool _glfw_get_key(RHIWindow window, RHIKeyCodeBits keycode)
{ return (glfwGetKey((GLFWwindow *) window, keycode) == GLFW_PRESS) ? RHI_PRESS : RHI_RELEASE; }

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

void _load_glfw_functions()
{
        if(!glfwInit()) {
                verror("ERROR - 初始化GLFW失败");
                exit(1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        ANCIRHICREATEWIDNOW             = _glfw_create_window;
        ANCIRHIWINDOWSHOULDCLOSE        = _glfw_should_clsoe;
        ANCIRHIWINDOWSETRESIZECALLBACK  = _glfw_set_window_resize_callback;
        ANCIRHIWINDOWPOLLEVENTS         = _glfw_poll_events;
        ANCIRHIDELETWINDOW              = _glfw_destroy_window;
        ANCIRHITERMINATE                = _glfw_terminate;
        ANCIRHIOPENGLGETCURRENTCONTEXT  = _glfw_get_current_context;
        ANCIRHIOPENGLMAKECONTEXTCURRENT = _glfw_make_context_current;
        ANCIRHIGETKEY                   = _glfw_get_key;
        ANCIRHISETCURSORINPUTMODE       = _glfw_set_cursor_mode;
        ANCIRHISETUSERPOINTER           = _glfw_set_user_pointer;
        ANCIRHIGETUSERPOINTER           = _glfw_get_user_pointer;
        ANCIRHIWINDOWSETCURSORCALLBACK  = _glfw_set_window_cursor_callback;
}