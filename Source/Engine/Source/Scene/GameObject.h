/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <RHI.h>
#include <blueprint.h>
#include <anci_core.h>
#include "Loader/ModelLoader.h"

// std
#include <vector>

/** 顶点布局 */
struct Vertex {
        ancivec3 position;
        ancivec3 normal;
        ancivec2 texcoord;
};

/** 渲染对象 */
class GameObject {
public:
        GameObject(mloader::mesh_t &meshs);
        ~GameObject();

        /* 设置模型位置 */
        inline void SetPosition (ancivec3 position)
        { _position = position; }

        /* 设置模型缩放比例 */
        inline void SetScale(ancivec3 scale)
        { _scale = scale;}

        /* 设置模型的旋转 */
        inline void SetRotation(ancivec3 rotation)
        { _rotation = rotation; }

        /* 模型矩阵 */
        inline ancimat4& GetModelMatrix()
        { return _model_matrix; }

        /* 渲染 */
        void Draw();

private:
        ancivec3                _position;
        ancivec3                _scale;
        ancivec3                _rotation;
        ancimat4                _model_matrix{1.0f};

        RHIVertexBuffer         _vtxbuf;
        RHIIndicesBuffer        _idxbuf;
        RHITexture              _texture;
};