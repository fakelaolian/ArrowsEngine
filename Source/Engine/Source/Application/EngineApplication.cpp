/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "EngineApplication.h"

#include <RHI.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

EngineApplication::EngineApplication()
{
        /* 初始化RHI函数 */
        RHIProcAddressInit(OpenGL);
        _window = make_anciptr<EngineWindow>("暗刺引擎", 800, 800);
}

struct RHIVtxBufferArray {
        ancivec3 pos;
        ancivec3 color;
        ancivec2 uv;
        ancivec3 normal;
};

void EngineApplication::StartEngine()
{

        RHIVtxBufferArray vertices[] = {
                {{0.5f,  0.5f,  0.0f}, {1.0f, 0.5f, 0.2f}, {1.0f, 1.0f}},
                {{0.5f,  -0.5f, 0.0f}, {1.0f, 0.5f, 0.2f}, {1.0f, 0.0f}},
                {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.5f, 0.2f}, {0.0f, 0.0f}},
                {{-0.5f, 0.5f,  0.0f}, {1.0f, 0.5f, 0.2f}, {0.0f, 1.0f}},
        };

        RHIVtxBufferLayout layouts[] = {
                {0, 3, RHI_FLOAT, offsetof(RHIVtxBufferArray, pos)},
                {1, 3, RHI_FLOAT, offsetof(RHIVtxBufferArray, color)},
                {2, 2, RHI_FLOAT, offsetof(RHIVtxBufferArray, uv)},
                {3, 3, RHI_FLOAT, offsetof(RHIVtxBufferArray, normal)},
        };

        RHIVtxBufferCreateInfo vtxBufferCreateInfo = {};
        vtxBufferCreateInfo.vertexCount = ARRAY_SIZE(vertices);
        vtxBufferCreateInfo.stride = sizeof(RHIVtxBufferArray);
        vtxBufferCreateInfo.pBufferLayout = layouts;
        vtxBufferCreateInfo.bufferLayoutCount = ARRAY_SIZE(layouts);

        RHIVtxBuffer vtxBuffer = RHIGenVtxBuffer(vertices, &vtxBufferCreateInfo);

        anciu32 indices[] = {
                0, 1, 3,
                1, 2, 3
        };
        RHIIdxBuffer idxBuffer = RHIGenIdxBuffer(indices, ARRAY_SIZE(indices));

        RHIShader shader = RHICreateShader("../../../Source/Engine/Shaders/simple.alsl");

        int width, height, ns;
        stbi_set_flip_vertically_on_load(true);
        anciuc *pixels = stbi_load("../../../Assets/container.jpg", &width, &height, &ns, 0);
        if (!pixels)
                throw std::runtime_error("加载纹理失败。");

        RHITexture texture0 = RHIGenTexture(RHI_IMAGE_FORMAT_RGB, width, height, pixels);
        stbi_image_free(pixels);

        pixels = stbi_load("../../../Assets/awesomeface.png", &width, &height, &ns, 0);
        if (!pixels)
                throw std::runtime_error("加载纹理失败。");

        RHITexture texture1 = RHIGenTexture(RHI_IMAGE_FORMAT_RGBA, width, height, pixels);
        stbi_image_free(pixels);

        RHIBindShader(shader);
        RHIUniform1i(shader, "ourSampler2D_0", 0);
        RHIUniform1i(shader, "ourSampler2D_1", 1);

        bool show_demo_window = false;
        float zNear = 0.01f, zFar = 100.0f, degrees = 45.0f;
        ancivec3 viewXYZ(0.0f, 0.0f, -3.0f);
        float rotateDegrees = -55.0f;
        ancivec3 rotateXZY(1.0f, 0.0f, 0.0f);

        while (!_window->ShouldClose()) {
                _window->PollEvents();

                RHIClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);

                ancimat4 model{1.0f};
                ancimat4 projection{1.0f};
                ancimat4 view{1.0f};
                model = glm::rotate(model, glm::radians(rotateDegrees), rotateXZY);
                view = glm::translate(view, viewXYZ);
                RHIDimension dimension = _window->GetDimension();
                projection = glm::perspective(glm::radians(degrees), (float) dimension.x / (float) dimension.y, zNear, zFar);

                RHIUniformMatrix4fv(shader, "model", glm::value_ptr(model));
                RHIUniformMatrix4fv(shader, "view", glm::value_ptr(view));
                RHIUniformMatrix4fv(shader, "proj", glm::value_ptr(projection));

                RHIBindTexture(texture0);
                RHIBindTexture(texture1);
                RHIBindVtxBuffer(vtxBuffer);
                RHIDrawIdx(idxBuffer);

                RHISwapBuffers(_window->GetHandle());
        }
}