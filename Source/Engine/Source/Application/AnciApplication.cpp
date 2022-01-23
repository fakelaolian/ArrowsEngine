/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "AnciApplication.h"

#include "Scene/Scene.h"
#include "ImGui/ImGui_Performance.h"

// std
#include <time.h>

AnciApplication::AnciApplication(const char *title, uint32_t w, uint32_t h)
{
        _window = make_anciptr<AnciWindow>(title, w, h);
        _gui    = make_anciptr<AnciGUI>(_window->GetHandle());
}

void AnciApplication::Run()
{
        Scene defaultScene{*_window};

        float _delta_time = 0.0f, _current_time = 0.0f, _last_time = 0.0f;
        clock_t _draw_time  = 0L;

        /* 游戏主循环 */
        RHIEnable(RHI_DEPTH_TEST, RHI_TRUE);
        while(!_window->ShouldClose()) {
                RHIPollEvents();
                RHIClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);

                /* deltaTime */
                _current_time = RHIGetTime();
                _delta_time   = _current_time - _last_time;
                _last_time    = _current_time;

                _draw_time = clock();
                defaultScene.Update(_delta_time);
                defaultScene.Render();
                _draw_time = clock() - _draw_time;

                _gui->BeginRender(); {
                        bool show = true;
                        ImGui::ShowDemoWindow(&show);
                        /* 性能面板 */
                        COMP_ImGUI_Performance_Data performance_data;
                        performance_data.DeltaTime = _delta_time;
                        performance_data.DrawTime  = _draw_time;
                        COMP_ImGUI_Performance_Draw(&performance_data);
                } _gui->EndRender();

                RHISwapBuffers(_window->GetHandle());
        }
}