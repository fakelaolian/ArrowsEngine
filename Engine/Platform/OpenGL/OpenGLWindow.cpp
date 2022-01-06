/* AUTHOR: BlazeStark, DATE: 2022/1/6 */
#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(const String &title, ancivec2 dimension) : AnciWindow(title, dimension)
{
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window_handle = glfwCreateWindow((int) dimension.x, (int) dimension.y, title.c_str(), nullptr, nullptr);
}