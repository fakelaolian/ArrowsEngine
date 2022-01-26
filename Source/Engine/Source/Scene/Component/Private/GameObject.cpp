/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "Scene/Component/GameObject.h"
#include "Loader/TextureLoader.h"

GameObject::GameObject(const char *name, mloader::mesh_t &mesh) : GameComponent(name, this)
{
        /* 创建顶点缓冲区 */
        std::vector<Vertex> vertices;
        vertices.resize(mesh.vertices.size());

        void *src = mesh.vertices.data();
        void *dst = vertices.data();
        memcpy(dst, src, mesh.vertices.size() * sizeof(mloader::vertex_t));

        ArsVertexBufferLayout layouts[] = {
                {0, 3, ARS_TYPE_FORMAT_FLOAT, offsetof(Vertex, position)},
                {1, 3, ARS_TYPE_FORMAT_FLOAT, offsetof(Vertex, normal)},
                {2, 2, ARS_TYPE_FORMAT_FLOAT, offsetof(Vertex, texcoord)},
        };

        ArsVertexBufferMemLayoutInfo memLayoutInfo{};
        memLayoutInfo.bufferLayoutCount = ARRAY_SIZE(layouts);
        memLayoutInfo.pBufferLayout = layouts;
        memLayoutInfo.stride = sizeof(Vertex);
        memLayoutInfo.vertexCount = mesh.vertices.size();
        memLayoutInfo.pVertices = vertices.data();

        ArsCreateVertexBuffer(&memLayoutInfo, &_vtxbuf);

        /* 创建索引缓冲区 */
        ArsCreateIndicesBuffer(mesh.indices.data(), mesh.indices.size(), &_idxbuf);

        /* 创建纹理 */
        ArsTexture2DCreateInfo textureCreateInfo{};
        textureCreateInfo.format = ARS_IMAGE_FORMAT_RGBA;
        textureCreateInfo.textureFilterMin = ARS_TEXTURE_FILTER_NEAREST;
        textureCreateInfo.textureFilterMag = ARS_TEXTURE_FILTER_NEAREST;
        textureCreateInfo.textureWrapS = ARS_TEXTURE_WRAP_MIRRORED_REPEAT;
        textureCreateInfo.textureWrapT = ARS_TEXTURE_WRAP_MIRRORED_REPEAT;

        int w, h, nc;
        arsuc *pixels = _stbi_load(mesh.texture, &w, &h, &nc, 0);
        textureCreateInfo.width = w;
        textureCreateInfo.height = h;
        textureCreateInfo.pPixels = pixels;
        ArsCreateTexture2D(&textureCreateInfo, &_texture);

        _stbi_image_free(pixels);
}

GameObject::~GameObject()
{
        ArsDestroyTexture(_texture);
        ArsDestroyVertexBuffer(_vtxbuf);
        ArsDestroyIndicesBuffer(_idxbuf);
}

void GameObject::Draw()
{
        ArsBindVertexBuffer(_vtxbuf);
        ArsBindTexture(ARS_TEXTURE_2D, _texture);
        ArsDrawIndices(_idxbuf);
}