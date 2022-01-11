/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#include <AnciWindow.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct CallbackUserPointer {
        RESIZE_CALLBACK _resize_callback;
};

class OpenGLWindow : public AnciWindow {
public:
        OpenGLWindow                               (const String& title, ancivec2 dimension);
        ~OpenGLWindow                              ()                         { glfwDestroyWindow(_window_handle); glfwTerminate(); }
        inline ANCI_WINDOW_HANDLE GetHandle        () override                { return _window_handle; };
        inline bool               ShouldClose      () override                { return glfwWindowShouldClose(_window_handle); };
        inline void               PollEvents       () override                { glfwPollEvents(); };
        void                      SetResizeCallback(RESIZE_CALLBACK callback) override;

private:
        GLFWwindow*               _window_handle;
        CallbackUserPointer       _callback_user_pointer;

};
