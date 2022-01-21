/* AUTHOR: 2BKBD, DATE: 2022/1/20 */
#pragma once

#include <anci_core.h>

class Camera {
public:
        Camera(ancivec3 pos) : _position(pos) {}

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
        ancivec3 _position;
        ancivec3 _front;
        ancivec3 _up;
        ancivec3 _right;
        ancivec3 _world_up;

        /* 相机属性 */
        float _move_speed = 1.0f;
        float _sensitive  = 1.0f;
};