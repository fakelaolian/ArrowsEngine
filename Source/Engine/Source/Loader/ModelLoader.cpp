/* AUTHOR: 2BKBD, DATE: 2022/1/17 */
#include "ModelLoader.h"

#include <iostream>
#include <fstream>
#include "Tools/StringUtils.h"
#include <unordered_map>

#include "Format/obj.h"
#include "Format/fbx.h"

namespace anci {
        attribute_t * load_model(const char *file, model_format_bits format)
        {
                switch (format) {
                        case ANCI_MODEL_FORMAT_OBJ_BIT: return load_model_obj(file);
                        case ANCI_MODEL_FORMAT_FBX_BIT: return load_model_fbx(file);
                }
        }

        void free_model(attribute_t * attribute)
        {
                free_model_obj(attribute);
        }
}