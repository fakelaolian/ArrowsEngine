/* AUTHOR: 2BKBD, DATE: 2022/1/20 */
#pragma once

#include <anci_core.h>

class Camera {
public:
        enum CameraMovement {
                CAMERA_MOVE_FRONT,
                CAMERA_MOVE_BACK,
                CAMERA_MOVE_RIGHT,
                CAMERA_MOVE_LEFT,
        };

        Camera(ancivec3 position, ancivec3 target, ancivec3 wordUp)
        {
                _position = position;
                _world_up = wordUp;
                _forward  = glm::normalize(target - position);
                _right    = glm::normalize(glm::cross(_forward, _world_up));
                _up       = glm::normalize(glm::cross(_forward, _right));
        }

        virtual void Update(float aspect) = 0;

        inline void SetMoveSpeed(float speed)
        { _move_speed = speed; }

        inline void SetSensitive(float sensitive)
        { _sensitive = sensitive; }

        inline ancimat4& GetProjectionMatrix()
        { return _projection_matrix; }

        inline ancimat4& GetViewMatrix()
        { return _view_matrix; }

protected:
        ancimat4 _view_matrix{1.0f};
        ancimat4 _projection_matrix{1.0f};

        /* 变换要计算的数据 */
        ancivec3 _position{0.0f, 0.0f, -5.0f};
        ancivec3 _up;
        ancivec3 _right;
        ancivec3 _forward;
        ancivec3 _world_up;

        /* 相机属性 */
        float _move_speed = 2.5f;
        float _sensitive  = 1.0f;
};