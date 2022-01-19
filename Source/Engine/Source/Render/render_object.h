/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <RHI.h>
#include <anci_math.h>
#include <blueprint.h>
#include <vector>

/**
 * 网格对象
 */
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

/**
 * 渲染对象
 */
class BLUEPRINT_CARD(RenderObject) {
public:
        RenderObject();
        ~RenderObject();

        inline void
        BLUEPRINT_NODE(SetPosition)(ancivec3 position)
        { _position = position; }

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
        ancimat4                _model_matrix;
};