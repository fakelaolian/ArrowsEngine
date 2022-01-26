/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "MainApplication.h"

#include "Scene/Scene.h"
#include "ImGui/GUIKIT.h"

// std
#include <time.h>

MainApplication::MainApplication(const char *title, uint32_t w, uint32_t h)
{
        _window = make_arosptr<MainWindow>(title, w, h);
        _gui    = make_arosptr<APPGUI>(_window->GetHandle());
        _guikit = make_arosptr<GUIKit>();
}

void MainApplication::Run()
{
        Scene defaultScene{*_window};

        float _delta_time, _current_time, _last_time = 0.0f;
        clock_t _draw_time;

        ArsFramebuffer framebuffer;
        ArsFramebufferCreateInfo createInfo = {};
        createInfo.width = _window->GetWidth();
        createInfo.height = _window->GetHeight();

        ArsCreateFramebuffer(&createInfo, &framebuffer);

        /* 游戏主循环 */
        ArsEnable(ARS_DEPTH_TEST, ARS_TRUE);
        while(!_window->ShouldClose()) {
                ArsBindFramebuffer(framebuffer);
                ArsClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);

                /* deltaTime */
                _current_time = ArsGetTime();
                _delta_time   = _current_time - _last_time;
                _last_time    = _current_time;

                _draw_time = clock();
                defaultScene.Update(_delta_time, _guikit->ASPECT);
                defaultScene.Render();
                _draw_time = clock() - _draw_time;

                ArsBindFramebuffer(ARS_FRAMEBUFFER0);
                ArsClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);
                _gui->BeginRender(); {
                        GUIKitData guiKitData;
                        guiKitData.deltaTime    = _delta_time;
                        guiKitData.drawTime     = _draw_time;
                        guiKitData.framebuffer  = framebuffer;
                        guiKitData.componentList= &defaultScene.GetComponentList();
                        _guikit->Render(&guiKitData);
                } _gui->EndRender();

                ArsSwapBuffers(_window->GetHandle());
                ArsPollEvents();
        }
}