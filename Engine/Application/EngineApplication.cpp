/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "EngineApplication.h"

#include <ATools/AnciCreator.h>
#include <RHI/RHI.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
                {{0.5f,  0.5f,  0.0f}, {1.0f, 0.5f, 0.2f}, {1.0f, 1.0f}},
                {{0.5f,  -0.5f, 0.0f}, {1.0f, 0.5f, 0.2f}, {1.0f, 0.0f}},
                {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.5f, 0.2f}, {0.0f, 0.0f}},
                {{-0.5f, 0.5f,  0.0f}, {1.0f, 0.5f, 0.2f}, {0.0f, 1.0f}},
        };

        anciu32 indices[] = {
                0, 1, 3,
                1, 2, 3
        };

        RHIShader shader = RHICreateShader("../Engine/Shaders/simple.alsl");
        RHIVtxBuffer vtxBuffer = RHIGenVtxBuffer(vertices, ARRAY_SIZE(vertices));
        RHIIdxBuffer idxBuffer = RHIGenIdxBuffer(indices, ARRAY_SIZE(indices));

        int width, height, ns;
        stbi_set_flip_vertically_on_load(true);
        anciuc *pixels = stbi_load("../Assets/container.jpg", &width, &height, &ns, 0);
        if (!pixels)
                throw std::runtime_error("加载纹理失败。");

        RHITexture texture0 = RHIGenTexture(RHI_IMAGE_FORMAT_RGB, width, height, pixels);
        stbi_image_free(pixels);

        pixels = stbi_load("../Assets/awesomeface.png", &width, &height, &ns, 0);
        if (!pixels)
                throw std::runtime_error("加载纹理失败。");

        RHITexture texture1 = RHIGenTexture(RHI_IMAGE_FORMAT_RGBA, width, height, pixels);
        stbi_image_free(pixels);

        shader->Bind();
        shader->SetInt("ourSampler2D_0", 0);
        shader->SetInt("ourSampler2D_1", 1);

        while (!_window->ShouldClose()) {
                RHIClearColorBuffer(ancivec4(0.2f));

                RHIBindTexture(texture0);
                RHIBindTexture(texture1);

                shader->Bind();
                RHIBindVtxBuffer(vtxBuffer);
                RHIDrawIdx(idxBuffer);

                RHISwapBuffers(_window->GetHandle());
                _window->PollEvents();
        }
}