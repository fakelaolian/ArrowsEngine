/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
#include "glfw.h"

#include "core.h"
#include <stdlib.h>

ANCI_RHI_CREATE_WINDOW                  ANCIRHICREATEWIDNOW                      = NULL;
ANCI_RHI_WINDOW_SHOULD_CLOSE            ANCIRHIWINDOWSHOULDCLOSE                 = NULL;
ANCI_RHI_WINDOW_SET_RESIZE_CALLBACK     ANCIRHIWINDOWSETRESIZECALLBACK           = NULL;
ANCI_RHI_WINDOW_POLL_EVENTS             ANCIRHIWINDOWPOLLEVENTS                  = NULL;
ANCI_RHI_DELETE_WINDOW                  ANCIRHIDELETWINDOW                       = NULL;
ANCI_RHI_TERMINATE                      ANCIRHITERMINATE                         = NULL;
ANCI_RHI_OPENGL_GET_CURRENT_CONTEXT     ANCIRHIOPENGLGETCURRENTCONTEXT           = NULL;
ANCI_RHI_OPENGL_MAKE_CONTEXT_CURRENT    ANCIRHIOPENGLMAKECONTEXTCURRENT          = NULL;
ANCI_RHI_GET_KEY                        ANCIRHIGETKEY                            = NULL;

F_RHI_WINDOW_RESIZE_CALLBACK            _window_resize_callback                  = NULL;

RHIWindow _glfw_create_window(const char *title, int width, int height)
{
        /* 初始化窗口 */
        GLFWwindow *_window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (_window == NULL) {
                verror("创建窗口失败");
                glfwTerminate();
                return NULL;
        }

        /* 初始化GLAD */
        glfwMakeContextCurrent(_window);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                glfwDestroyWindow(_window);
                glfwTerminate();

                verror("加载GLAD失败");
                return NULL;
        }

        return _window;
}

ancibool _glfw_should_clsoe(RHIWindow window)
{ return glfwWindowShouldClose((GLFWwindow *) window); }

void _glfw_set_window_resize_callback0(GLFWwindow *window, int x, int y)
{ _window_resize_callback(window, x, y); }

void _glfw_set_window_resize_callback(RHIWindow window, F_RHI_WINDOW_RESIZE_CALLBACK fcallback)
{
        _window_resize_callback = fcallback;
        glfwSetFramebufferSizeCallback((GLFWwindow *) window, _glfw_set_window_resize_callback0);}

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
}