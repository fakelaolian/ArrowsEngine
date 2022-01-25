/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <RHI.h>
#include <blueprint.h>
#include <arrows_core.h>
#include "Loader/ModelLoader.h"
#include "GameComponent.h"

// std
#include <vector>

/** 顶点布局 */
struct Vertex {
        arrovec3 position;
        arrovec3 normal;
        arrovec2 texcoord;
};

/** 渲染对象 */
class GameObject : public GameComponent<GameObject> {
public:
        GameObject(const char *name, mloader::mesh_t &meshs);
        ~GameObject();

        /* 设置模型位置 */
        inline arrovec3& GetPosition ()
        { return _position; }

        /* 设置模型缩放比例 */
        inline arrovec3& GetScale()
        { return _scale; }

        /* 设置模型的旋转 */
        inline arrovec3& GetRotation()
        { return _rotation; }

        /* 模型矩阵 */
        inline arromat4& GetModelMatrix()
        {
                const float c3 = glm::cos(_rotation.z);
                const float s3 = glm::sin(_rotation.z);
                const float c2 = glm::cos(_rotation.x);
                const float s2 = glm::sin(_rotation.x);
                const float c1 = glm::cos(_rotation.y);
                const float s1 = glm::sin(_rotation.y);
                _model_matrix = glm::mat4{
                        {
                                _scale.x * (c1 * c3 + s1 * s2 * s3),
                                _scale.x * (c2 * s3),
                                _scale.x * (c1 * s2 * s3 - c3 * s1),
                                0.0f, },
                        {
                                _scale.y * (c3 * s1 * s2 - c1 * s3),
                                _scale.y * (c2 * c3),
                                _scale.y * (c1 * c3 * s2 + s1 * s3),
                                0.0f,
                        },
                        {
                                _scale.z * (c2 * s1),
                                _scale.z * (-s2),
                                _scale.z * (c1 * c2),
                                0.0f,
                        },
                        {
                                _position.x,
                                _position.y,
                                _position.z,
                                1.0f
                        }
                };

                return _model_matrix;
        }

        /* 渲染 */
        void Draw();

private:
        arrovec3                _position{0.0f};
        arrovec3                _scale{1.0f};
        arrovec3                _rotation{0.0f};
        arromat4                _model_matrix{1.0f};

        RHIVertexBuffer         _vtxbuf;
        RHIIndicesBuffer        _idxbuf;
        RHITexture              _texture;
};