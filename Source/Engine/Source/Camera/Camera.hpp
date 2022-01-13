/* AUTHOR: 2BKBD, DATE: 2022/1/11 */
#pragma once

#include <AnciCore.h>

class Camera {
public:
        Camera()
        {
        }

        inline const
        ancimat4 &GetViewMatrix()
        {
                float radius = 10.0f;
                float camX = sin(RHIGetTime()) * radius;
                float camZ = cos(RHIGetTime()) * radius;
                _view_matrix = glm::lookAt(glm::vec3(camX, 0.0, camZ),
                                           glm::vec3(0.0, 0.0, 0.0),
                                           glm::vec3(0.0, 1.0, 0.0));

                return _view_matrix;
        }

private:
        ancimat4 _view_matrix;

};