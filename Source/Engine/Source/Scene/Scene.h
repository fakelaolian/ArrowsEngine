/* AUTHOR: 2BKBD, DATE: 2022/1/21 */
#pragma once

#include "Scene/Component/SkyBox.h"
#include "Scene/Component/GameObject.h"
#include "Application/MainWindow.h"
#include "Component/SceneComponentList.h"

// std
#include <vector>

class Scene {
public:
        Scene(MainWindow& window);
        ~Scene();

        inline SceneComponentList &GetComponentList()
        { return _component_list; }

        void Update(float deltaTime, float aspect);
        void Render();

private:
        MainWindow&             _window;
        std::vector<GameObject> _objects;
        RHIShader               _normalize_shader;
        arroptr<SkyBox>         _skybox;
        SceneCamera             _camera{
                {0.0f, 0.0f, -8.0f},
                0.0f, 0.0f,
                {0.0f, 1.0f, 0.0f}
        };

        SceneComponentList      _component_list{};
};