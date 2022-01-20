/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "render_object.h"

RenderMesh::RenderMesh()
{
}

RenderMesh::~RenderMesh()
{
        RHIDestroyTexture(_texture);
        RHIDestroyVtxBuffer(_vtx_buffer);
        RHIDestroyIdxBuffer(_idx_buffer);
}

void RenderMesh::Draw()
{
        RHIBindTexture(RHI_TEXTURE_2D, _texture);
        RHIBindVtxBuffer(_vtx_buffer);
        RHIDrawIdx(_idx_buffer);
}

RenderObject::RenderObject()
{

}