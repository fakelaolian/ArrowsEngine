/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <Ars.h>
#include <blueprint.h>
#include <arrows_core.h>
#include "Loader/ModelLoader.h"
#include "GameComponent.h"

// std
#include <vector>

/** 顶点布局 */
struct Vertex {
        arosvec3 position;
        arosvec3 normal;
        arosvec2 texcoord;
};

/* 3D变换 */
struct Transform3D {
        arosvec3 position{0.0f};
        arosvec3 scale{1.0f};
        arosvec3 rotation{0.0f};

        /* 模型矩阵 */
        arosmat4& GetModelMatrix();

private:
        arosmat4 _model_matrix;
};

/** 渲染对象 */
class GameObject : public GameComponent<GameObject> {
public:
        Transform3D transform3D;

public:
        GameObject(const char *name, mloader::mesh_t &meshs);
        ~GameObject();

        /* 获取材质 */
        inline ArsTexture& GetTexture()
        { return _texture; }

        /* 渲染 */
        void Draw();

private:
        ArsVertexBuffer         _vtxbuf;
        ArsIndicesBuffer        _idxbuf;
        ArsTexture              _texture;
};