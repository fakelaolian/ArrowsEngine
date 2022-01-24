/* AUTHOR: 2BKBD, DATE: 2022/1/23 */
#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

unsigned char *_stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp)
{ return stbi_load(filename, x, y, comp, req_comp); }

void _stbi_image_free(void *p_data)
{ stbi_image_free(p_data); }