/* AUTHOR: 2BKBD, DATE: 2022/1/21 */
#include "Scene.h"

Scene::Scene(MainWindow& window) : _window(window)
{
        std::vector<mloader::mesh_t> meshs = mloader::load_model("../../../Assets/untitled.obj");
        meshs[0].texture = "../../../Assets/container2.png";

        _objects.emplace_back("正方体", meshs[0]);
        _normalize_shader = ArsCreateShader(GET_SHADER(normalize.alsl));

        ////////////////////////////////////////////////////////////
        ////////                   天空盒                    ////////
        ////////////////////////////////////////////////////////////
        std::vector<const char *> skyboxsImage = {
                "../../../Assets/skyboxs/a/right.jpg",
                "../../../Assets/skyboxs/a/left.jpg",
                "../../../Assets/skyboxs/a/top.jpg",
                "../../../Assets/skyboxs/a/bottom.jpg",
                "../../../Assets/skyboxs/a/front.jpg",
                "../../../Assets/skyboxs/a/back.jpg",
        };

        _skybox = make_arroptr<SkyBox>("默认天空盒", skyboxsImage.data());

        /* 添加到组件列表 */
        _component_list.PutGameComponent(_objects[0]);
//        _component_list.PushComponent(*_skybox);
}

Scene::~Scene()
{

}

void Scene::Update(float deltaTime, float aspect)
{
        if (ArsGetMouseButton(_window.GetHandle(), ARS_MOUSE_BUTTON_2) == ARS_PRESS) {
                _window.DisableCursor();

                /* 控制相机移动 */
                if (ArsGetKey(_window.GetHandle(), ARS_KEY_W) == ARS_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_FORWARD, deltaTime);
                if (ArsGetKey(_window.GetHandle(), ARS_KEY_S) == ARS_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_BACK, deltaTime);
                if (ArsGetKey(_window.GetHandle(), ARS_KEY_A) == ARS_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_RIGHT, deltaTime);
                if (ArsGetKey(_window.GetHandle(), ARS_KEY_D) == ARS_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_LEFT, deltaTime);
                if (ArsGetKey(_window.GetHandle(), ARS_KEY_SPACE) == ARS_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_UP, deltaTime);
                if (ArsGetKey(_window.GetHandle(), ARS_KEY_LEFT_CONTROL) == ARS_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_DOWN, deltaTime);

                _camera.Rotate(_window.GetMouseX(), _window.GetMouseY());

        } else {
                _window.NormalCursor();
                _camera.ResetFirstMouseBit();
        }

        _camera.Update(aspect);

        /* 更新着色器 */
        ArsBindShader(_normalize_shader);
        ArsUniformMatrix4fv(_normalize_shader, "proj", glm::value_ptr(_camera.GetProjectionMatrix()));
        ArsUniformMatrix4fv(_normalize_shader, "view", glm::value_ptr(_camera.GetViewMatrix()));
}

void Scene::Render()
{
        for (auto &object : _objects) {
                ArsUniformMatrix4fv(_normalize_shader, "model", glm::value_ptr(object.GetModelMatrix()));
                object.Draw();
        }

        _skybox->Draw(_normalize_shader, _camera);
}