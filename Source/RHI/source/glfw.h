/* AUTHOR: 2BKBD, DATE: 2022/1/13 */
#ifndef __GLFW_RHI_H__
#define __GLFW_RHI_H__

#include "RHI.h"

#ifndef GLFW_INCLUDE_VULKAN
#  include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>

/** 加载glfw函数 */
void _load_glfw_functions();

#endif /*__GLFW_RHI_H__*/
