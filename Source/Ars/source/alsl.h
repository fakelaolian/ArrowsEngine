/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
#ifndef __ALSL_H__
#define __ALSL_H__

#include "core.h"

typedef struct ShaderSource {
        const char *vtx;
        const char *frag;
} ShaderSource;

void load_shader_source(const char *file, ShaderSource *pSource);
void free_shader_source(ShaderSource *pSource);

#endif /*__ALSL_H__*/