/* AUTHOR: 2BKBD, DATE: 2022/1/21 */
#include "MainWindow.h"

MainWindow::MainWindow(const char *title, int w, int h)
{
        ArsProcAddressInit(OpenGL);

        /* 创建窗口 */
        ArsCreateWindow(title, w, h, &_window_handle);
        ArsSetUserPointer(_window_handle, this);

        _aspect = (float) w / h;

        /* 设置窗口回调函数 */
        ArsSetWindowResizeCallback(_window_handle, [](ArsWindow window, int w, int h) {
                MainWindow *app = (MainWindow *) ArsGetUserPointer(window);
                app->SetDimension(w, h);
        });

        ArsSetWindowCursorCallback(_window_handle, [](ArsWindow window, double x, double y){
                MainWindow *app = (MainWindow *) ArsGetUserPointer(window);
                app->SetMouseXY((float) x, (float) y);
        });

        if (!_window_handle)
                throw std::runtime_error("创建窗口失败。");

        _width  = w;
        _height = h;
}

MainWindow::~MainWindow()
{
        ArsDestroyWindow(_window_handle);
        ArsTerminate();
}
