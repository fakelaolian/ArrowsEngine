/* AUTHOR: 2BKBD, DATE: 2022/1/20 */
#pragma once

#include <anci_core.h>
#include "Render/Camera.h"

/** 场景相机 */
class SceneCamera : public Camera {
public:
        SceneCamera(ancivec3 position, ancivec3 target, ancivec3 wordUp) : Camera(position, target, wordUp) {}

        inline void Move(CameraMovement movement, float deltaTime)
        {
                if (movement == CAMERA_MOVE_FRONT)
                        _position.z += _move_speed * deltaTime;
                if (movement == CAMERA_MOVE_BACK)
                        _position.z -= _move_speed * deltaTime;
                if (movement == CAMERA_MOVE_RIGHT)
                        _position.x += _move_speed * deltaTime;
                if (movement == CAMERA_MOVE_LEFT)
                        _position.x -= _move_speed * deltaTime;
        }

        inline void Update(float aspect) override
        {
                _projection_matrix =
                        glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

                _view_matrix = glm::lookAt(_position, _position + _forward, _world_up);
        }
};