/* AUTHOR: 2BKBD, DATE: 2022/1/22 */
#include "Scene/Component/SkyBox.h"
#include "SkyBoxArray.h"
#include "Loader/TextureLoader.h"

SkyBox::SkyBox(const char *name, const char ** faces) : GameComponent(name, this)
{
        /* 加载顶点数据 */
        ArsVertexBufferLayout layouts[] = {
                {0, 3, ARS_TYPE_FORMAT_FLOAT, 0}
        };

        ArsVertexBufferMemLayoutInfo memLayoutInfo = {};
        memLayoutInfo.vertexCount = ARRAY_SIZE(_SkyBoxArray) / 3;
        memLayoutInfo.stride = sizeof(float) * 3;
        memLayoutInfo.pVertices = _SkyBoxArray;
        memLayoutInfo.bufferLayoutCount = ARRAY_SIZE(layouts);
        memLayoutInfo.pBufferLayout = layouts;

        ArsCreateVertexBuffer(&memLayoutInfo, &_vtx_buffer);

        /* 加载立方体贴图 */
        ArsTextureCubeCreateInfo createInfo ={};
        createInfo.textureFilterMin = ARS_TEXTURE_FILTER_LINEAR;
        createInfo.textureFilterMag = ARS_TEXTURE_FILTER_LINEAR;
        createInfo.textureWrapS = ARS_TEXTURE_WRAP_CLAMP_TO_EDGE;
        createInfo.textureWrapT = ARS_TEXTURE_WRAP_CLAMP_TO_EDGE;
        createInfo.textureWrapR = ARS_TEXTURE_WRAP_CLAMP_TO_EDGE;

        int w, h, nc;
        for (int i = 0; i < 6; i++) {
                arsuc *pixels = _stbi_load(faces[i], &w, &h, &nc, 0);

                createInfo.format[i]   = ARS_IMAGE_FORMAT_RGB;
                createInfo.width[i]    = w;
                createInfo.height[i]   = h;
                createInfo.pPixels[i]  = pixels;
        }

        ArsCreateTextureCubeMap(&createInfo, &_skybox_texture);

        for (auto p_data : createInfo.pPixels) {
                _stbi_image_free(p_data);
        }

        /* 加载着色器 */
        _skybox_shader = ArsCreateShader("../../../Source/Engine/Shaders/skybox.alsl");
}

SkyBox::~SkyBox()
{
        ArsDestroyShader(_skybox_shader);
        ArsDestroyVertexBuffer(_vtx_buffer);
        ArsDestroyTexture(_skybox_texture);
}

void SkyBox::Draw(ArsShader &currentShader, SceneCamera &camera)
{
        ArsDepthOption(ARS_DEPTH_OPTION_LE);
        ArsBindShader(_skybox_shader);
        arromat4 skyboxView = arromat4(arromat3(camera.GetViewMatrix()));
        ArsUniformMatrix4fv(currentShader, "view", glm::value_ptr(skyboxView));
        ArsUniformMatrix4fv(currentShader, "proj", glm::value_ptr(camera.GetProjectionMatrix()));
        ArsBindTexture(ARS_TEXTURE_CUBE_MAP, _skybox_texture);
        ArsBindVertexBuffer(_vtx_buffer);
        ArsDrawVtx(0, 36);
        ArsDepthOption(ARS_DEPTH_OPTION_LT);
}