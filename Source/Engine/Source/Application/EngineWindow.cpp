/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "EngineWindow.h"

EngineWindow::EngineWindow(const char *title, int w, int h)
{
        _window = RHICreateWindow(title, w, h);
        _dimension = {w, h};

        RHISetUserPointer(_window, this);
        RHISetWindowResizeCallback(_window, [](RHIWindow window, int w, int h) {
                EngineWindow *_window = (EngineWindow *) RHIGetUserPointer(window);
                _window->SetDimension(w, h);
                RHIViewport(0, 0, w, h);
        });

        RHISetWindowCursorCallback(_window, [](RHIWindow window, double x, double  y) {
                EngineWindow *_window = (EngineWindow *) RHIGetUserPointer(window);
                _window->SetCursor((float) x, (float) y);
        });

}