/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <Ars.h>
#include <blueprint.h>
#include <arrows_core.h>
#include "GameComponent.h"
#include "Private/GameMesh.h"

// std
#include <vector>

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
        GameObject(const char *name, std::vector<arosloader::mesh_t> &meshs);
        ~GameObject();

        const std::vector<GameMesh *>& GetMeshs()
        { return _meshs; }

        /* 渲染 */
        void Draw(ArsShader shader);

private:
        std::vector<GameMesh *> _meshs;

};