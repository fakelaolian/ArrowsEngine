/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "MainApplication.h"

#include "Scene/Scene.h"
#include "ImGui/GUIKIT.h"

// std
#include <time.h>

MainApplication::MainApplication(const char *title, uint32_t w, uint32_t h)
{
        _window = make_arroptr<MainWindow>(title, w, h);
        _gui    = make_arroptr<APPGUI>(_window->GetHandle());
}

void MainApplication::Run()
{
        Scene defaultScene{*_window};

        float _delta_time = 0.0f, _current_time = 0.0f, _last_time = 0.0f;
        clock_t _draw_time  = 0L;

        RHIFramebuffer framebuffer;
        RHIFramebufferCreateInfo createInfo = {};
        createInfo.width = _window->GetWidth();
        createInfo.height = _window->GetHeight();

        RHICreateFramebuffer(&createInfo, &framebuffer);

        /* 游戏主循环 */
        RHIEnable(RHI_DEPTH_TEST, RHI_TRUE);
        while(!_window->ShouldClose()) {
                RHIBindFramebuffer(framebuffer);
                RHIClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);

                /* deltaTime */
                _current_time = RHIGetTime();
                _delta_time   = _current_time - _last_time;
                _last_time    = _current_time;

                _draw_time = clock();
                defaultScene.Update(_delta_time, GUIKit::ASPECT);
                defaultScene.Render();
                _draw_time = clock() - _draw_time;

                RHIBindFramebuffer(RHI_FRAMEBUFFER0);
                RHIClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);
                _gui->BeginRender(); {
                        GUIKitData guiKitData;
                        guiKitData.deltaTime    = _delta_time;
                        guiKitData.drawTime     = _draw_time;
                        guiKitData.framebuffer  = framebuffer;
                        GUIKit::Render(&guiKitData);
                } _gui->EndRender();

                RHISwapBuffers(_window->GetHandle());
                RHIPollEvents();
        }
}