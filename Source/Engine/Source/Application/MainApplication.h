/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <RHI.h>
#include <arrows_core.h>
#include "MainWindow.h"
#include "ImGui/APPGUI.h"
#include "ImGui/GUIKIT.h"

class MainApplication {
public:
        MainApplication(const char *title, uint32_t w, uint32_t h);
        ~MainApplication() = default;

        void Run();

private:
        arroptr<MainWindow> _window;
        arroptr<APPGUI>    _gui;
        arroptr<GUIKit>    _guikit;

};