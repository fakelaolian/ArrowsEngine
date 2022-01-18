/* AUTHOR: 2BKBD, DATE: 2022/1/17 */
#pragma once

#include <vector>

namespace anci {

typedef enum model_format_bits {
        ANCI_MODEL_FORMAT_OBJ_BIT,
        ANCI_MODEL_FORMAT_FBX_BIT,
} model_format_bits;

typedef struct material_t {

} material_t;

typedef struct vertex_t {
        float pos[3];
        float uv[2];
        float normal[3];
        bool operator==(const vertex_t &other) const {
                return (pos[0] == other.pos[0] && pos[1] == other.pos[1] && pos[2] == other.pos[2]) &&
                       (uv[0] == other.uv[0] && uv[1] == other.uv[1]) &&
                       (normal[0] == other.normal[0] && normal[2] == other.normal[1] && normal[2] == other.normal[2]);
        };
} vertex_t;

typedef struct mesh_t {
        std::vector<vertex_t> vertices;
        std::vector<int> indices;
} mesh_t;

struct attribute_t {
        std::vector<mesh_t> meshs;
};

attribute_t *load_model(const char *file, model_format_bits format);
void free_model(const char *file);

}