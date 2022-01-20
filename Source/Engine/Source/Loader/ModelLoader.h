/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <vector>
#include <cstdint>

namespace mloader {

struct vertex_t {
        float vertex[3];
        float normal[3];
        float texcoord[2];
};

struct mesh_t {
        std::vector<vertex_t> vertices;
        std::vector<uint32_t> indices;
        const char *          texture;
};

/** 加载模型 */
std::vector<mesh_t> load_model(const char *filename);

}