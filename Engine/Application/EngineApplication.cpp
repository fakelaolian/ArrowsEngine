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
        float vertices[] = {
                0.5f,  0.5f, 0.0f,  // top right
                0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left
        };

        anciu32 indices[] = {
                0, 1, 3,
                1, 2, 3
        };

        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                           "}\n\0";

        RHIShader vtxShader = RHICreateShader(vertexShaderSource, RHI_VERTEX_SHADER);
        RHIShader fragShader = RHICreateShader(fragmentShaderSource, RHI_FRAGMENT_SHADER);
        RHIShaderProgram shaderProgram = RHICreateShaderProgram(vtxShader, fragShader);

        RHIVtxBuffer vtxBuffer = RHIGenVtxBuffer(vertices, sizeof(vertices) / sizeof(float));
        RHIIdxBuffer idxBuffer = RHIGenIdxBuffer(indices, sizeof(indices) / sizeof(anciu32));

        while (!_window->ShouldClose()) {
                RHIClear(ancivec4(0.2f));

                RHIBindShaderProgram(shaderProgram);
                RHIBindVtxBuffer(vtxBuffer);
                RHIDrawIdx(idxBuffer);

                RHISwapBuffers(_window->GetHandle());
                _window->PollEvents();
        }
}