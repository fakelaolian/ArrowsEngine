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

struct attribute_t {
        std::vector<float> vertices;
        std::vector<float> texcoords;
        std::vector<float> normals;
        unsigned long count;
        material_t *material;
};

attribute_t *load_model(const char *file, model_format_bits format);
void free_model(const char *file);

}