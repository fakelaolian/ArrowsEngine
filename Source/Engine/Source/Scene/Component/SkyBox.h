/* AUTHOR: 2BKBD, DATE: 2022/1/22 */
#pragma once

#include <RHI.h>
#include <arrows_core.h>
#include "Scene/SceneCamera.h"
#include "GameComponent.h"

class SkyBox : public GameComponent<SkyBox> {
public:
        SkyBox(const char *name, const char * faces[6]);
        ~SkyBox();
        void Draw(RHIShader &currentShader, SceneCamera &camera);

private:
        RHIShader _skybox_shader;
        RHIVertexBuffer _vtx_buffer;
        RHITexture _skybox_texture;

};