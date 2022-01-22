/* AUTHOR: 2BKBD, DATE: 2022/1/23 */
#pragma once

unsigned char *_stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
void _stbi_image_free(void *p_data);