/* AUTHOR: 2BKBD, DATE: 2022/1/20 */
#pragma once

#include <arrows_core.h>
#include "Scene/Component/GameComponent.h"

class Camera{
public:
        enum CameraMovement {
                CAMERA_MOVE_FORWARD,
                CAMERA_MOVE_BACK,
                CAMERA_MOVE_RIGHT,
                CAMERA_MOVE_LEFT,
                CAMERA_MOVE_UP,
                CAMERA_MOVE_DOWN,
        };

        Camera(arosvec3 position, float pitch, float yaw, arosvec3 wordUp)
        {
                _position  = position;
                _world_up  = wordUp;
                _pitch     = pitch;
                _yaw       = yaw;

                UpdateVectors();
        }

        inline void UpdateVectors()
        {
                arosvec3 forward;
                forward.x = cos(_yaw) * cos(_pitch);
                forward.y = sin(_pitch);
                forward.z = sin(_yaw) * cos(_pitch);
                _forward  = normalize(forward);

                _right    = glm::normalize(glm::cross(_forward, _world_up));
                _up       = glm::normalize(glm::cross(_right, _forward));
        }

        virtual void Update(float aspect) = 0;

        inline void SetMoveSpeed(float speed)
        { _move_speed = speed; }

        inline void SetSensitive(float sensitive)
        { _sensitive = sensitive; }

        inline arosmat4& GetProjectionMatrix()
        { return _projection_matrix; }

        inline arosmat4& GetViewMatrix()
        { return _view_matrix; }

protected:
        arosmat4 _view_matrix{1.0f};
        arosmat4 _projection_matrix{1.0f};

        /* 变换要计算的数据 */
        arosvec3 _position{0.0f, 0.0f, -5.0f};
        arosvec3 _up;
        arosvec3 _right;
        arosvec3 _forward;
        arosvec3 _world_up;
        float    _pitch;
        float    _yaw;
        float    _last_mouse_x;
        float    _last_mouse_y;

        /* 相机属性 */
        float _move_speed = 10.0f;
        float _sensitive  = 0.001f;
};