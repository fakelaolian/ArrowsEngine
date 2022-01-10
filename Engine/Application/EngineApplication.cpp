/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "EngineApplication.h"

#include <ATools/AnciCreator.h>
#include <RHI/RHI.h>

AnciEnumGraphicsApi g_AnciGraphicsApi;

EngineApplication::EngineApplication(AnciEnumGraphicsApi api)
{
        g_AnciGraphicsApi = api;
        _window = AnciCreateWindow("太古引擎", ancivec2(800, 800));

        /* 初始化RHI函数 */
        RHIApiLoad();
}

void EngineApplication::StartEngine()
{
        while (!_window->ShouldClose()) {
                _window->PollEvents();
                RHISwapBuffers(_window->GetHandle());
        }
}