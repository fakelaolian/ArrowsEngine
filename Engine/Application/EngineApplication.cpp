/* AUTHOR: BlazeStark, DATE: 2022/1/6 */
#include "EngineApplication.h"
#include <AnciCreator.h>

AnciEnumGraphicsApi g_AnciGraphicsApi;

EngineApplication::EngineApplication(AnciEnumGraphicsApi api)
{
        g_AnciGraphicsApi = api;
}

EngineApplication::~EngineApplication()
{

}

void EngineApplication::StartEngine()
{
        _window = AnciCreateWindow("太古引擎", ancivec2(800, 800));
        while (!_window->ShouldClose()) {
                _window->PollEvents();
        }
}