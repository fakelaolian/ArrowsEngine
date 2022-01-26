/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <Ars.h>
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
        arosptr<MainWindow> _window;
        arosptr<APPGUI>    _gui;
        arosptr<GUIKit>    _guikit;

};