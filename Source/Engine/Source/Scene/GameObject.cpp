/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "GameObject.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GameObject::GameObject(mloader::mesh_t &mesh)
{
        /* 创建顶点缓冲区 */
        std::vector<Vertex> vertices;
        vertices.resize(mesh.vertices.size());

        void *src = mesh.vertices.data();
        void *dst = vertices.data();
        memcpy(dst, src, mesh.vertices.size() * sizeof(mloader::vertex_t));

        RHIVertexBufferLayout layouts[] = {
                {0, 3, RHI_FLOAT, offsetof(Vertex, position)},
                {1, 3, RHI_FLOAT, offsetof(Vertex, normal)},
                {2, 2, RHI_FLOAT, offsetof(Vertex, texcoord)},
        };

        RHIVertexBufferMemLayoutInfo memLayoutInfo{};
        memLayoutInfo.bufferLayoutCount = ARRAY_SIZE(layouts);
        memLayoutInfo.pBufferLayout = layouts;
        memLayoutInfo.stride = sizeof(Vertex);
        memLayoutInfo.vertexCount = mesh.vertices.size();

        RHICreateVertexBuffer(vertices.data(), &memLayoutInfo, &_vtxbuf);

        /* 创建索引缓冲区 */
        RHICreateIndicesBuffer(mesh.indices.data(), mesh.indices.size(), &_idxbuf);

        /* 创建纹理 */
        RHITexture2DCreateInfo textureCreateInfo{};
        textureCreateInfo.format = RHI_IMAGE_FORMAT_RGBA;
        textureCreateInfo.textureFilterMin = RHI_TEXTURE_FILTER_NEAREST;
        textureCreateInfo.textureFilterMag = RHI_TEXTURE_FILTER_NEAREST;
        textureCreateInfo.textureWrapS = RHI_TEXTURE_WRAP_MIRRORED_REPEAT;
        textureCreateInfo.textureWrapT = RHI_TEXTURE_WRAP_MIRRORED_REPEAT;

        int w, h, nc;
        anciuc *pixels = stbi_load(mesh.texture, &w, &h, &nc, 0);
        textureCreateInfo.width = w;
        textureCreateInfo.height = h;
        textureCreateInfo.pPixels = pixels;
        RHICreateTexture2D(&textureCreateInfo, &_texture);

        stbi_image_free(pixels);
}

GameObject::~GameObject()
{
        RHIDestroyTexture(_texture);
        RHIDestroyVertexBuffer(_vtxbuf);
        RHIDestroyIndicesBuffer(_idxbuf);
}

void GameObject::Draw()
{
        RHIBindVertexBuffer(_vtxbuf);
        RHIBindTexture(RHI_TEXTURE_2D, _texture);
        RHIDrawIndices(_idxbuf);
}
