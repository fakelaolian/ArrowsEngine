/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "EngineApplication.h"

#include <ATools/AnciCreator.h>
#include <RHI/RHI.h>

AnciEnumGraphicsApi g_AnciGraphicsApi;

EngineApplication::EngineApplication(AnciEnumGraphicsApi api)
{
        g_AnciGraphicsApi = api;
        _window = AnciCreateWindow("暗刺引擎", ancivec2(800, 800));

        /* 初始化RHI函数 */
        RHIApiLoad();
}

void EngineApplication::StartEngine()
{
        RHIVtxArray vertices[] = {
                {{0.5f,  0.5f,  0.0f}, {0.2f, 0.2f, 0.2f}},
                {{0.5f,  -0.5f, 0.0f}, {0.2f, 0.2f, 0.2f}},
                {{-0.5f, -0.5f, 0.0f}, {0.2f, 0.2f, 0.2f}},
                {{-0.5f, 0.5f,  0.0f}, {0.2f, 0.2f, 0.2f}},
        };

        anciu32 indices[] = {
                0, 1, 3,
                1, 2, 3
        };

        RHIShader shader = RHICreateShader("../Engine/Shaders/simple.alsl");
        RHIVtxBuffer vtxBuffer = RHIGenVtxBuffer(vertices, ARRAY_SIZE(vertices));
        RHIIdxBuffer idxBuffer = RHIGenIdxBuffer(indices, ARRAY_SIZE(indices));

        while (!_window->ShouldClose()) {
                RHIClearColorBuffer(ancivec4(0.2f));

                shader->Bind();
                RHIBindVtxBuffer(vtxBuffer);
                RHIDrawIdx(idxBuffer);

                RHISwapBuffers(_window->GetHandle());
                _window->PollEvents();
        }
}