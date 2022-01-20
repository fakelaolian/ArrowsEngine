/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <RHI.h>
#include <anci_math.h>
#include <blueprint.h>
#include <vector>

/** 顶点布局 */
struct RenderVertex {
        ancivec3 position;
        ancivec3 normal;
        ancivec2 texcoord;
};

/** 网格对象 */
class RenderMesh {
public:
        RenderMesh();
        ~RenderMesh();

        void Draw();

private:
        RHIVtxBuffer _vtx_buffer;
        RHIIdxBuffer _idx_buffer;
        RHITexture   _texture;
};

/** 渲染对象 */
class RenderObject {
public:
        RenderObject();
        ~RenderObject();

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

        inline void Draw()
        {
                for (RenderMesh &mesh : _meshs)
                        mesh.Draw();
        }

private:
        std::vector<RenderMesh> _meshs;
        ancivec3                _position;
        ancivec3                _scale;
        ancivec3                _rotation;
        ancimat4                _model_matrix;
};