/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "GameObject.h"

Mesh::Mesh(mloader::mesh_t &mesh)
{
        /* 创建顶点缓冲区 */
        std::vector<Vertex> vertices;
        vertices.resize(mesh.vertices.size());

        void *src = mesh.vertices.data();
        void *dst = vertices.data();
        memcpy(dst, src, mesh.vertices.size() * sizeof(mloader::vertex_t));

        RHIVtxBufferLayout layouts[] = {
                {0, 3, RHI_FLOAT, offsetof(Vertex, position)},
                {1, 3, RHI_FLOAT, offsetof(Vertex, normal)},
                {2, 2, RHI_FLOAT, offsetof(Vertex, texcoord)},
        };

        RHIVtxBufferMemLayoutInfo memLayoutInfo{};
        memLayoutInfo.bufferLayoutCount = ARRAY_SIZE(layouts);
        memLayoutInfo.pBufferLayout = layouts;
        memLayoutInfo.stride = sizeof(Vertex);
        memLayoutInfo.vertexCount = mesh.vertices.size();

        RHICreateVertexBuffer(dst, &memLayoutInfo, &_vtx_buffer);

        /* 创建索引缓冲区 */
        RHICreateIndicesBuffer(mesh.indices.data(), mesh.indices.size(), &_idx_buffer);
}

Mesh::~Mesh()
{
//        RHIDestroyTexture(_texture);
        RHIDestroyVertexBuffer(_vtx_buffer);
        RHIDestroyIndicesBuffer(_idx_buffer);
}

void Mesh::Draw()
{
        RHIBindVertexBuffer(_vtx_buffer);
//        RHIBindTexture(RHI_TEXTURE_2D, _texture);
        RHIDrawIndices(_idx_buffer);
}

GameObject::GameObject(std::vector<mloader::mesh_t> &meshs)
{
        for (mloader::mesh_t &mesh : meshs)
                _meshs.push_back(new Mesh(mesh));
}
