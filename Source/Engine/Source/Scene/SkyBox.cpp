/* AUTHOR: 2BKBD, DATE: 2022/1/22 */
#include "SkyBox.h"
#include "SkyBoxArray.h"
#include "Loader/TextureLoader.h"

SkyBox::SkyBox(const char ** faces)
{
        /* 加载顶点数据 */
        RHIVertexBufferLayout layouts[] = {
                {0, 3, RHI_FLOAT, 0}
        };

        RHIVertexBufferMemLayoutInfo memLayoutInfo = {};
        memLayoutInfo.vertexCount = ARRAY_SIZE(_SkyBoxArray) / 3;
        memLayoutInfo.stride = sizeof(float) * 3;
        memLayoutInfo.pVertices = _SkyBoxArray;
        memLayoutInfo.bufferLayoutCount = ARRAY_SIZE(layouts);
        memLayoutInfo.pBufferLayout = layouts;

        RHICreateVertexBuffer(&memLayoutInfo, &_vtx_buffer);

        /* 加载立方体贴图 */
        RHITextureCubeCreateInfo createInfo ={};
        createInfo.textureFilterMin = RHI_TEXTURE_FILTER_LINEAR;
        createInfo.textureFilterMag = RHI_TEXTURE_FILTER_LINEAR;
        createInfo.textureWrapS = RHI_TEXTURE_WRAP_CLAMP_TO_EDGE;
        createInfo.textureWrapT = RHI_TEXTURE_WRAP_CLAMP_TO_EDGE;
        createInfo.textureWrapR = RHI_TEXTURE_WRAP_CLAMP_TO_EDGE;

        int w, h, nc;
        for (int i = 0; i < 6; i++) {
                anciuc *pixels = _stbi_load(faces[i], &w, &h, &nc, 0);

                createInfo.format[i]   = RHI_IMAGE_FORMAT_RGB;
                createInfo.width[i]    = w;
                createInfo.height[i]   = h;
                createInfo.pPixels[i]  = pixels;
        }

        RHICreateTextureCubeMap(&createInfo, &_skybox_texture);

        for (auto p_data : createInfo.pPixels) {
                _stbi_image_free(p_data);
        }

        /* 加载着色器 */
        _skybox_shader = RHICreateShader("../../../Source/Engine/Shaders/skybox.alsl");
}

SkyBox::~SkyBox()
{
        RHIDestroyShader(_skybox_shader);
        RHIDestroyVertexBuffer(_vtx_buffer);
        RHIDestroyTexture(_skybox_texture);
}

void SkyBox::Draw(RHIShader &currentShader, SceneCamera &camera)
{
        RHIDepthOption(RHI_DEPTH_OPTION_LE);
        RHIBindShader(_skybox_shader);
        ancimat4 skyboxView = ancimat4(ancimat3(camera.GetViewMatrix()));
        RHIUniformMatrix4fv(currentShader, "view", glm::value_ptr(skyboxView));
        RHIUniformMatrix4fv(currentShader, "proj", glm::value_ptr(camera.GetProjectionMatrix()));
        RHIBindTexture(RHI_TEXTURE_CUBE_MAP, _skybox_texture);
        RHIBindVertexBuffer(_vtx_buffer);
        RHIDrawVtx(0, 36);
        RHIDepthOption(RHI_DEPTH_OPTION_LT);
}