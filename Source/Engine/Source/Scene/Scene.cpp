/* AUTHOR: 2BKBD, DATE: 2022/1/21 */
#include "Scene.h"

Scene::Scene(AnciWindow& window) : _window(window)
{
        std::vector<mloader::mesh_t> meshs = mloader::load_model("C:/Users/procf/Desktop/untitled.obj");
        meshs[0].texture = "D:\\projects\\AnciEngine\\Assets\\container2.png";

        _objects.emplace_back(meshs[0]);
        _normalize_shader = RHICreateShader(GET_SHADER(normalize.alsl));
}

Scene::~Scene()
{

}

void Scene::Update(float deltaTime)
{
        if (RHIGetMouseButton(_window.GetHandle(), RHI_MOUSE_BUTTON_2) == RHI_PRESS) {
                _window.DisableCursor();

                /* 控制相机移动 */
                if (RHIGetKey(_window.GetHandle(), RHI_KEY_W) == RHI_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_FORWARD, deltaTime);
                if (RHIGetKey(_window.GetHandle(), RHI_KEY_S) == RHI_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_BACK, deltaTime);
                if (RHIGetKey(_window.GetHandle(), RHI_KEY_A) == RHI_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_RIGHT, deltaTime);
                if (RHIGetKey(_window.GetHandle(), RHI_KEY_D) == RHI_PRESS)
                        _camera.Move(Camera::CAMERA_MOVE_LEFT, deltaTime);

                _camera.Rotate(_window.GetMouseX(), _window.GetMouseY());

        } else {
                _window.NormalCursor();
                _camera.ResetFirstMouseBit();
        }

        _camera.Update(_window.GetAspect());

        /* 更新着色器 */
        RHIBindShader(_normalize_shader);
        RHIUniformMatrix4fv(_normalize_shader, "proj", glm::value_ptr(_camera.GetProjectionMatrix()));
        RHIUniformMatrix4fv(_normalize_shader, "view", glm::value_ptr(_camera.GetViewMatrix()));
}

void Scene::Render()
{
        for (auto &object : _objects) {
                RHIUniformMatrix4fv(_normalize_shader, "model", glm::value_ptr(object.GetModelMatrix()));
                object.Draw();
        }
}