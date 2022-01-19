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
        BLUEPRINT_NODE(SetPosition)(ancivec3 pos)
        { _pos = pos; }

        inline void Draw()
        {
                for (RenderMesh &mesh : _meshs)
                        mesh.Draw();
        }

private:
        ancivec3                _pos;
        std::vector<RenderMesh> _meshs;
};