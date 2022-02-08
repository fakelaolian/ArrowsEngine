/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "Scene/Component/GameObject.h"

arosmat4& Transform3D::GetModelMatrix()
{
        const float c3 = glm::cos(rotation.z);
        const float s3 = glm::sin(rotation.z);
        const float c2 = glm::cos(rotation.x);
        const float s2 = glm::sin(rotation.x);
        const float c1 = glm::cos(rotation.y);
        const float s1 = glm::sin(rotation.y);
        _model_matrix = glm::mat4{
                {
                        scale.x * (c1 * c3 + s1 * s2 * s3),
                        scale.x * (c2 * s3),
                        scale.x * (c1 * s2 * s3 - c3 * s1),
                        0.0f, },
                {
                        scale.y * (c3 * s1 * s2 - c1 * s3),
                        scale.y * (c2 * c3),
                        scale.y * (c1 * c3 * s2 + s1 * s3),
                        0.0f,
                },
                {
                        scale.z * (c2 * s1),
                        scale.z * (-s2),
                        scale.z * (c1 * c2),
                        0.0f,
                },
                {
                        position.x,
                        position.y,
                        position.z,
                        1.0f
                }
        };

        return _model_matrix;
}

GameObject::GameObject(const char *name, std::vector<arosloader::mesh_t> &meshs) : GameComponent(name, this)
{
        for (arosloader::mesh_t &mesh : meshs)
                _meshs.push_back(new GameMesh(mesh));
}

GameObject::~GameObject()
{
        for (auto mesh : _meshs)
                delete mesh;
}

void GameObject::Draw(ArsShader shader)
{
        for (auto mesh : _meshs)
                mesh->Draw(transform3D.GetModelMatrix(), shader);
}