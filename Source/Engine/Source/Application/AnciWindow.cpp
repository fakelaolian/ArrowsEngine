/* AUTHOR: 2BKBD, DATE: 2022/1/21 */
#include "AnciWindow.h"

AnciWindow::AnciWindow(const char *title, int w, int h)
{
        RHIProcAddressInit(OpenGL);

        /* 创建窗口 */
        RHICreateWindow(title, w, h, &_window_handle);
        RHISetUserPointer(_window_handle, this);

        _aspect = (float) w / h;

        /* 设置窗口回调函数 */
        RHISetWindowResizeCallback(_window_handle, [](RHIWindow window, int w, int h) {
                AnciWindow *app = (AnciWindow *) RHIGetUserPointer(window);
                app->SetDimension(w, h);
        });

        RHISetWindowCursorCallback(_window_handle, [](RHIWindow window, double x, double y){
                AnciWindow *app = (AnciWindow *) RHIGetUserPointer(window);
                app->SetMouseXY((float) x, (float) y);
        });

        if (!_window_handle)
                throw std::runtime_error("创建窗口失败。");

        _width  = w;
        _height = h;
}

AnciWindow::~AnciWindow()
{
        RHIDestroyWindow(_window_handle);
        RHITerminate();
}
