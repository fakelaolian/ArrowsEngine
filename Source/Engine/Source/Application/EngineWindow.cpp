/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "EngineWindow.h"

EngineWindow::EngineWindow(const char *title, int w, int h)
{
        _window = RHICreateWindow(title, w, h);
        _dimension = {w, h};
}