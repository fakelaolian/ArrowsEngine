/* AUTHOR: 2BKBD, DATE: 2022/1/21 */
#pragma once

#include "SkyBox.h"
#include "GameObject.h"
#include "Application/AnciWindow.h"

// std
#include <vector>

class Scene {
public:
        Scene(AnciWindow& window);
        ~Scene();

        void Update(float deltaTime);
        void Render();

private:
        AnciWindow&             _window;
        std::vector<GameObject> _objects;
        RHIShader               _normalize_shader;
        anciptr<SkyBox>         _skybox;
        SceneCamera             _camera{
                {0.0f, 0.0f, -8.0f},
                0.0f, 0.0f,
                {0.0f, 1.0f, 0.0f}
        };
};