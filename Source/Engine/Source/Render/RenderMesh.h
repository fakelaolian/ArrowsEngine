/* AUTHOR: 2BKBD, DATE: 2022/1/18 */
#pragma once

#include <AnciCore.h>
#include <RHI.h>

#include "Loader/Loader.h"

struct Vertex {
        ancivec3 pos;
        ancivec3 normal;
        ancivec2 uv;
};

class RenderMesh {
public:
        RenderMesh(loader::mesh_t& mesh);
        void Draw();

private:
        anciu32      _vtx_count;
        RHIVtxBuffer _vtx_buffer;
        RHIIdxBuffer _idx_buffer;
        RHITexture   _texture;

};