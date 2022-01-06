/* AUTHOR: BlazeStark, DATE: 2022/1/6 */
#pragma once

#include <AnciWindow.h>
#include <GLFW/glfw3.h>

class OpenGLWindow : public AnciWindow {
public:
        OpenGLWindow                          (const String& title, ancivec2 dimension);
        ~OpenGLWindow                         ()            { glfwDestroyWindow(_window_handle); glfwTerminate(); }
        inline ANCI_WINDOW_HANDLE GetHandle   () override   { return _window_handle; };
        inline bool               ShouldClose () override   { return glfwWindowShouldClose(_window_handle); };
        inline void               PollEvents  () override   { glfwPollEvents(); };

private:
        GLFWwindow*                           _window_handle;

};
