/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "Scene/Component/GameObject.h"
#include "Loader/TextureLoader.h"

arosmat4& Transform3D::GetModelMatrix()
{
        const float c3 = glm::cos(rotation.z);
        const float s3 = glm::sin(rotation.z);
        const float c2 = glm::cos(rotation.x);
        const float s2 = glm::sin(rotation.x);
        const float c1 = glm::cos(rotation.y);
        const float s1 = glm::sin(rotation.y);
        _model_matrix = glm::mat4{
                {
                        scale.x * (c1 * c3 + s1 * s2 * s3),
                        scale.x * (c2 * s3),
                        scale.x * (c1 * s2 * s3 - c3 * s1),
                        0.0f, },
                {
                        scale.y * (c3 * s1 * s2 - c1 * s3),
                        scale.y * (c2 * c3),
                        scale.y * (c1 * c3 * s2 + s1 * s3),
                        0.0f,
                },
                {
                        scale.z * (c2 * s1),
                        scale.z * (-s2),
                        scale.z * (c1 * c2),
                        0.0f,
                },
                {
                        position.x,
                        position.y,
                        position.z,
                        1.0f
                }
        };

        return _model_matrix;
}

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