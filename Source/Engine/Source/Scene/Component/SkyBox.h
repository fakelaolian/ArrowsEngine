/* AUTHOR: 2BKBD, DATE: 2022/1/22 */
#pragma once

#include <Ars.h>
#include <arrows_core.h>
#include "Scene/SceneCamera.h"
#include "GameComponent.h"

class SkyBox : public GameComponent<SkyBox> {
public:
        SkyBox(const char *name, const char * faces[6]);
        ~SkyBox();
        void Draw(ArsShader &currentShader, SceneCamera &camera);

private:
        ArsShader _skybox_shader;
        ArsVertexBuffer _vtx_buffer;
        ArsTexture _skybox_texture;

};