/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(const String &title, ancivec2 dimension) : AnciWindow(title, dimension)
{
        if (!glfwInit())
                throw std::runtime_error("初始化GLFW失败。");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* 初始化窗口 */
        _window_handle = glfwCreateWindow((int) dimension.x, (int) dimension.y, title.c_str(), nullptr, nullptr);
        if (_window_handle == NULL) {
                glfwTerminate();
                throw std::runtime_error("创建窗口创建失败。");
        }

        /* 初始化GLAD */
        glfwMakeContextCurrent(_window_handle);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                glfwDestroyWindow(_window_handle);
                glfwTerminate();
                throw std::runtime_error("加载GLAD失败。");
        }

        glfwSetWindowUserPointer(_window_handle, this);
}

void OpenGLWindow::SetResizeCallback(RESIZE_CALLBACK callback)
{
        _callback_user_pointer._resize_callback = callback;
        glfwSetFramebufferSizeCallback(_window_handle, [](GLFWwindow* window, int width, int height){
                auto *glWindow = (OpenGLWindow *) glfwGetWindowUserPointer(window);
                glWindow->_callback_user_pointer._resize_callback(width, height);
                glWindow->_dimension = {width, height};
        });
}