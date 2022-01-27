/* AUTHOR: 2BKBD, DATE: 2022/1/26 */
#include "GameMesh.h"
#include "Loader/TextureLoader.h"

GameMesh::GameMesh(arosloader::mesh_t &mesh)
{
        /* 创建顶点缓冲区 */
        std::vector<Vertex> vertices;
        vertices.resize(mesh.vertices.size());

        _name = mesh.name;

        void *src = mesh.vertices.data();
        void *dst = vertices.data();
        memcpy(dst, src, mesh.vertices.size() * sizeof(arosloader::vertex_t));

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

        /* 加载纹理 */
        std::string basepath = "../../../Assets/nanosuit/";
        std::string path = basepath + mesh.material.map_kd;
        _diffuse_texture = LoadTextures(path);

        if (!mesh.material.map_ks.empty()) {
                path = basepath + mesh.material.map_ks;
                _specular_texture = LoadTextures(path);
        }
}

GameMesh::~GameMesh()
{
        ArsDestroyTexture(_diffuse_texture);
        if (_specular_texture != ARS_NULL_HANDLE)
                ArsDestroyTexture(_specular_texture);

        ArsDestroyVertexBuffer(_vtxbuf);
        ArsDestroyIndicesBuffer(_idxbuf);
}

ArsTexture GameMesh::LoadTextures(std::string& path)
{
        ArsTexture ret;

        /* 创建纹理 */
        ArsTexture2DCreateInfo textureCreateInfo{};
        textureCreateInfo.textureFilterMin = ARS_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR;
        textureCreateInfo.textureFilterMag = ARS_TEXTURE_FILTER_LINEAR;
        textureCreateInfo.textureWrapS = ARS_TEXTURE_WRAP_REPEAT;
        textureCreateInfo.textureWrapT = ARS_TEXTURE_WRAP_REPEAT;

        int w, h, channel;
        arsuc *pixels = _stbi_load(path.c_str(), &w, &h, &channel, 0);
        textureCreateInfo.width = w;
        textureCreateInfo.height = h;
        textureCreateInfo.pPixels = pixels;
        if (channel == 1)
                textureCreateInfo.format = ARS_IMAGE_FORMAT_RED;
        else if (channel == 3)
                textureCreateInfo.format = ARS_IMAGE_FORMAT_RGB;
        else if (channel == 4)
                textureCreateInfo.format = ARS_IMAGE_FORMAT_RGBA;
        ArsCreateTexture2D(&textureCreateInfo, &ret);

        _stbi_image_free(pixels);

        return ret;
}

void GameMesh::Draw(arosmat4& mat4, ArsShader shader)
{
        ArsUniformMatrix4fv(shader, "model", glm::value_ptr(mat4));

        ArsUniform1i(shader, "texture_diffuse", 1);
        ArsBindTexture(ARS_TEXTURE_2D, _diffuse_texture);
        if (_specular_texture != ARS_NULL_HANDLE)
                ArsBindTexture(ARS_TEXTURE_2D, _specular_texture);
        else
                ArsBindTexture(ARS_TEXTURE_2D, _diffuse_texture);

        ArsBindVertexBuffer(_vtxbuf);
        ArsDrawIndices(_idxbuf);
}