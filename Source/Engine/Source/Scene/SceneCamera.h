/* AUTHOR: 2BKBD, DATE: 2022/1/20 */
#pragma once

#include <arrows_core.h>
#include "Render/Camera.h"

/** 场景相机 */
class SceneCamera : public Camera {
public:
        SceneCamera(arrovec3 position, float pitch, float yaw, arrovec3 wordUp)
                : Camera(position, pitch, yaw, wordUp) {}

        /* 移动相机 */
        inline void Move(CameraMovement movement, float deltaTime, float incremental = 0.0f)
        {
                float vspeed = (_move_speed + incremental) * deltaTime;

                if (movement == CAMERA_MOVE_FORWARD)
                        _position += _forward * vspeed;
                if (movement == CAMERA_MOVE_BACK)
                        _position -= _forward * vspeed;
                if (movement == CAMERA_MOVE_RIGHT)
                        _position -= _right * vspeed;
                if (movement == CAMERA_MOVE_LEFT)
                        _position += _right * vspeed;
                if (movement == CAMERA_MOVE_UP)
                        _position.y += vspeed;
                if (movement == CAMERA_MOVE_DOWN)
                        _position.y -= vspeed;

                UpdateVectors();
        }

        inline void SetPosition(arrovec3 position)
        { _position = position; }

        /* 旋转相机 */
        inline void Rotate(float x, float y)
        {
                if(_first_mouse_bit) {
                        _last_mouse_x = x;
                        _last_mouse_y = y;
                        _first_mouse_bit = false;
                }

                float xoffset = (x - _last_mouse_x) * _sensitive;
                float yoffset = (_last_mouse_y - y) * _sensitive;

                _last_mouse_x = x;
                _last_mouse_y = y;

                _yaw   += xoffset;
                _pitch += yoffset;

                if (_pitch > 89.0f)
                        _pitch = 89.0f;
                if (_pitch < -89.0f)
                        _pitch = -89.0f;

                UpdateVectors();
        }

        inline void Update(float aspect) override
        {
                _projection_matrix =
                        glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

                _view_matrix = glm::lookAt(_position, _position + _forward, _world_up);
        }

        inline void ResetFirstMouseBit()
        { _first_mouse_bit = true; }

private:
        bool _first_mouse_bit = true;

};