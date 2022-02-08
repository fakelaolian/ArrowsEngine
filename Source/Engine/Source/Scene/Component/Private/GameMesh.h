/* AUTHOR: 2BKBD, DATE: 2022/1/26 */
#pragma once

#include <Ars.h>
#include <arrows_core.h>
#include "Loader/ModelLoader.h"

/** 顶点布局 */
struct Vertex {
        arosvec3 position;
        arosvec3 normal;
        arosvec2 texcoord;
};

class GameMesh {
public:
        GameMesh(arosloader::mesh_t &mesh);
        ~GameMesh();
        void Draw(arosmat4& mat4, ArsShader shader);

        const std::string& GetName()
        { return _name; }

        const std::vector<ArsTexture> &GetTextures()
        { return _textures;}

private:
        static ArsTexture LoadTextures(std::string& path);

private:
        std::string             _name;
        ArsVertexBuffer         _vtxbuf;
        ArsIndicesBuffer        _idxbuf;
        ArsTexture              _diffuse_texture = ARS_NULL_HANDLE;
        ArsTexture              _specular_texture = ARS_NULL_HANDLE;

        std::vector<ArsTexture> _textures;

};
