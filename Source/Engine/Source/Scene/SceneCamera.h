/* AUTHOR: 2BKBD, DATE: 2022/1/20 */
#pragma once

#include <anci_core.h>
#include "Render/Camera.h"

/** 场景相机 */
class SceneCamera : public Camera {
public:
        SceneCamera(ancivec3 pos = ancivec3(1.0f)) : Camera(pos) {}
        void Update(float aspect) override;

        void SetView(ancimat4 mat1)
        { _view_matrix = mat1; }
};