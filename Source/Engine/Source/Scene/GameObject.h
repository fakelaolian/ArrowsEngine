/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <RHI.h>
#include <blueprint.h>
#include <arrows_core.h>
#include "Loader/ModelLoader.h"

// std
#include <vector>

/** 顶点布局 */
struct Vertex {
        arrovec3 position;
        arrovec3 normal;
        arrovec2 texcoord;
};

/** 渲染对象 */
class GameObject {
public:
        GameObject(mloader::mesh_t &meshs);
        ~GameObject();

        /* 设置模型位置 */
        inline void SetPosition (arrovec3 position)
        { _position = position; }

        /* 设置模型缩放比例 */
        inline void SetScale(arrovec3 scale)
        { _scale = scale;}

        /* 设置模型的旋转 */
        inline void SetRotation(arrovec3 rotation)
        { _rotation = rotation; }

        /* 模型矩阵 */
        inline arromat4& GetModelMatrix()
        {
                _model_matrix = glm::translate(_model_matrix, _position);
                return _model_matrix;
        }

        /* 渲染 */
        void Draw();

private:
        arrovec3                _position;
        arrovec3                _scale;
        arrovec3                _rotation;
        arromat4                _model_matrix{1.0f};

        RHIVertexBuffer         _vtxbuf;
        RHIIndicesBuffer        _idxbuf;
        RHITexture              _texture;
};