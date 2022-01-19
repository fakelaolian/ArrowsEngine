/* AUTHOR: 2BKBD, DATE: 2022/1/18 */
#include "RenderMesh.h"

#include <iostream>

RenderMesh::RenderMesh(loader::mesh_t& mesh)
{
        std::vector<Vertex> vertices;
        vertices.resize(mesh.vertices.size());
        /* 复制mesh的数据到vertices生成顶点缓冲 */
        void *data = vertices.data();
        memcpy(data, mesh.vertices.data(), vertices.size() * sizeof(Vertex));

        RHIVtxBufferLayout layouts[] = {
                {0, 3, RHI_FLOAT, offsetof(Vertex, pos)},
                {1, 3, RHI_FLOAT, offsetof(Vertex, normal)},
                {2, 2, RHI_FLOAT, offsetof(Vertex, uv)},
        };

        RHIVtxBufferMemLayoutInfo memLayoutInfo = {};
        memLayoutInfo.pBufferLayout = layouts;
        memLayoutInfo.bufferLayoutCount = ARRAY_SIZE(layouts);
        memLayoutInfo.stride = sizeof(Vertex);
        memLayoutInfo.vertexCount = vertices.size();

        RHIGenVtxBuffer(data, &memLayoutInfo, &_vtx_buffer);
        RHIGenIdxBuffer(mesh.indices.data(), mesh.indices.size(), &_idx_buffer);
}

void RenderMesh::Draw()
{
        RHIBindVtxBuffer(_vtx_buffer);
        RHIDrawIdx(_idx_buffer);
}