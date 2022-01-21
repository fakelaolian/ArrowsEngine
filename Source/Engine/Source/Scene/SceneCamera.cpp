/* AUTHOR: 2BKBD, DATE: 2022/1/20 */
#include "SceneCamera.h"

void SceneCamera::Update(float aspect)
{
        _projection_matrix =
                glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

        _view_matrix = ancimat4{1.0f};
        _view_matrix = glm::translate(_view_matrix, ancivec3(0.0f, 0.0f, -5.0f));
}
