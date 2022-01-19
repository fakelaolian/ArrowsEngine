/* AUTHOR: 2BKBD, DATE: 2022/1/18 */
#pragma once

#include <AnciCore.h>
#include <RHI.h>

struct Vertex {
        ancivec3 pos;
        ancivec2 uv;
        ancivec3 normal;
};

class RenderMesh {
public:
        RenderMesh();
        void Draw();

private:
        anciu32      _vtx_count;
        RHIVtxBuffer _vtx_buffer;
        RHIIdxBuffer _idx_buffer;
        RHITexture   _texture;

};