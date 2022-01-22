/* AUTHOR: 2BKBD, DATE: 2022/1/22 */
#include "SkyBox.h"
#include "SkyBoxArray.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

SkyBox::SkyBox(const char ** skyboxs)
{
        /* 加载顶点数据 */
        RHIVertexBufferLayout layouts[] = {
                {0, 3, RHI_FLOAT, 0}
        };

        RHIVertexBufferMemLayoutInfo memLayoutInfo = {};
        memLayoutInfo.vertexCount = ARRAY_SIZE(_SkyBoxArray);
        memLayoutInfo.stride = sizeof(float);
        memLayoutInfo.pVertices = _SkyBoxArray;
        memLayoutInfo.bufferLayoutCount = ARRAY_SIZE(layouts);
        memLayoutInfo.pBufferLayout = layouts;

        RHICreateVertexBuffer(&memLayoutInfo, &_vtx_buffer);

        /* 加载立方体贴图 */
        RHITextureCubeCreateInfo createInfo ={};
        createInfo.textureFilterMin = RHI_TEXTURE_FILTER_LINEAR;
        createInfo.textureFilterMag = RHI_TEXTURE_FILTER_LINEAR;
        createInfo.textureWrapS = RHI_TEXTURE_WRAP_REPEAT;
        createInfo.textureWrapT = RHI_TEXTURE_WRAP_REPEAT;
        createInfo.textureWrapR = RHI_TEXTURE_WRAP_REPEAT;

        int w, h, nc;
        for (int i = 0; i < 6; i++) {
                anciuc *pixels = stbi_load(skyboxs[i], &w, &h, &nc, 0);

                createInfo.format[i]   = RHI_IMAGE_FORMAT_RGB;
                createInfo.width[i]    = w;
                createInfo.height[i]   = h;
                createInfo.pPixels[i]  = pixels;
        }

        RHICreateTextureCubeMap(&createInfo, &_skybox_texture);

        for (auto p_data : createInfo.pPixels) {
                stbi_image_free(p_data);
        }

        /* 加载着色器 */
        _skybox_shader = RHICreateShader("../../../Source/Engine/Shaders/skybox.alsl");
}

SkyBox::~SkyBox()
{

}

void SkyBox::Draw(ancimat4 viewMatrix)
{
        RHIDepthOption(RHI_DEPTH_OPTION_LE);
        RHIBindShader(_skybox_shader);
        ancimat4 skyboxView = ancimat4(ancimat3(viewMatrix));
        RHIUniformMatrix4fv(cubeShader, "view", glm::value_ptr(skyboxView));
        RHIUniformMatrix4fv(cubeShader, "projection", glm::value_ptr(projection));
        RHIBindTexture(RHI_TEXTURE_CUBE_MAP, _skybox_texture);
        RHIBindVertexBuffer(_vtx_buffer);
        RHIDrawVtx(0, 36);
        RHIDepthOption(RHI_DEPTH_OPTION_LT);
}