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

/** 网格对象 */
class Mesh {
public:
        Mesh(mloader::mesh_t &meshs);
        ~Mesh();

        void Draw();

private:
        RHIVtxBuffer _vtx_buffer;
        RHIIdxBuffer _idx_buffer;
        RHITexture   _texture;
};

/** 渲染对象 */
class GameObject {
public:
        GameObject(std::vector<mloader::mesh_t> &meshs);
        ~GameObject() = default;

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
        inline ancimat4 GetModelMatrix()
        { return _model_matrix; }

        /* 渲染 */
        inline void Draw()
        {
                for (Mesh *mesh : _meshs) {
                        mesh->Draw();
                }
        }

private:
        std::vector<Mesh*>      _meshs;
        ancivec3                _position;
        ancivec3                _scale;
        ancivec3                _rotation;
        ancimat4                _model_matrix;
};