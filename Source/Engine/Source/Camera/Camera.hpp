/* AUTHOR: 2BKBD, DATE: 2022/1/11 */
#pragma once

#include <AnciCore.h>

class Camera {
public:
        Camera()
        {
        }

        inline void Update(RHIWindow window, float dt)
        {
                float speed = 1.0f * dt;
                if (RHIGetKey(window, RHI_KEY_W) == RHI_PRESS)
                        _camera_pos += speed * _camera_front;
                if (RHIGetKey(window, RHI_KEY_S) == RHI_PRESS)
                        _camera_pos -= speed * _camera_front;
                if (RHIGetKey(window, RHI_KEY_A) == RHI_PRESS)
                        _camera_pos -= glm::normalize(glm::cross(_camera_front, _camera_up)) * speed;
                if (RHIGetKey(window, RHI_KEY_D) == RHI_PRESS)
                        _camera_pos += glm::normalize(glm::cross(_camera_front, _camera_up)) * speed;

        }

        inline const
        ancimat4 &GetViewMatrix()
        {
                _view_matrix = glm::lookAt(_camera_pos, _camera_pos + _camera_front, _camera_up);
                return _view_matrix;
        }

private:
        ancivec3 _camera_pos{0.0f, 0.0f, 3.0f};
        ancivec3 _camera_front{0.0f, 0.0f, -1.0f};
        ancivec3 _camera_up{0.0f, -1.0f, 0.0f};
        ancimat4 _view_matrix;

};