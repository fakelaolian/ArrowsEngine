/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace arosloader {

struct vertex_t {
        float vertex[3];
        float normal[3];
        float texcoord[2];
};

struct material_t {
        float       ns;
        float       ka[3];
        float       kd[3];
        float       ks[3];
        float       ni;
        float       d;
        int         illum;
        std::string map_kd;
        std::string map_bump;
        std::string map_ks;
};

struct mesh_t {
        std::vector<vertex_t> vertices;
        std::vector<uint32_t> indices;
        const char *          texture;
        material_t            material;
        std::string           name;
};

/** 加载模型 */
std::vector<mesh_t> load_model(const char *filename, std::vector<mesh_t> &mmeshs);

}