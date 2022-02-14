/* AUTHOR: 2BKBD, DATE: 2022/1/21 */
#include "Scene.h"

Scene::Scene(MainWindow& window) : _window(window)
{
        std::vector<arosloader::mesh_t> mmeshs;
        std::vector<arosloader::mesh_t> meshs = arosloader::load_model("../../../Assets/nanosuit/nanosuit.obj", mmeshs);

        _objects.emplace_back("纳米先知", meshs);
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

        _skybox = make_arosptr<SkyBox>("默认天空盒", skyboxsImage.data());

        /* 添加到组件列表 */
        _component_list.PutGameComponent(_objects[0]);
}

Scene::~Scene()
{

}

void Scene::Update(SceneEventData* p_data)
{
        if (p_data->MouseButton2Press) {
                _window.DisableCursor();

                /* 控制相机移动 */
                if (p_data->MoveKey_W)
                        _camera.Move(Camera::CAMERA_MOVE_FORWARD, p_data->DetailTime);
                if (p_data->MoveKey_S)
                        _camera.Move(Camera::CAMERA_MOVE_BACK, p_data->DetailTime);
                if (p_data->MoveKey_A)
                        _camera.Move(Camera::CAMERA_MOVE_RIGHT, p_data->DetailTime);
                if (p_data->MoveKey_D)
                        _camera.Move(Camera::CAMERA_MOVE_LEFT, p_data->DetailTime);
                if (p_data->MoveKey_SPACE)
                        _camera.Move(Camera::CAMERA_MOVE_UP, p_data->DetailTime);
                if (p_data->MoveKey_LEFT_CTRL)
                        _camera.Move(Camera::CAMERA_MOVE_DOWN, p_data->DetailTime);

                _camera.Rotate(_window.GetMouseX(), _window.GetMouseY());

        } else {
                _window.NormalCursor();
                _camera.ResetFirstMouseBit();
        }

        _camera.Update(p_data->Aspect);

        /* 更新着色器 */
        ArsBindShader(_normalize_shader);
        ArsUniformMatrix4fv(_normalize_shader, "proj", glm::value_ptr(_camera.GetProjectionMatrix()));
        ArsUniformMatrix4fv(_normalize_shader, "view", glm::value_ptr(_camera.GetViewMatrix()));
}

void Scene::Render()
{
        for (auto &object : _objects) {
                ArsUniformMatrix4fv(_normalize_shader, "model", glm::value_ptr(object.transform3D.GetModelMatrix()));
                object.Draw(_normalize_shader);
        }

        _skybox->Draw(_normalize_shader, _camera);
}