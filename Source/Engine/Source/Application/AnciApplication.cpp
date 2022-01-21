/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "AnciApplication.h"

#include "Scene/Scene.h"

AnciApplication::AnciApplication(const char *title, uint32_t w, uint32_t h)
{
        _window = make_anciptr<AnciWindow>(title, w, h);
}

void AnciApplication::Run()
{
        Scene defaultScene{*_window};

        float _delta_time = 0.0f, _current_time = 0.0f, _last_time = 0.0f;

        /* 游戏主循环 */
        RHIEnable(RHI_DEPTH_TEST, RHI_TRUE);
        while(!_window->ShouldClose()) {
                RHIPollEvents();
                RHIClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);

                /* deltaTime */
                _current_time = RHIGetTime();
                _delta_time   = _current_time - _last_time;
                _last_time    = _current_time;

                defaultScene.Update(_delta_time);
                defaultScene.Render();

                RHISwapBuffers(_window->GetHandle());
        }
}