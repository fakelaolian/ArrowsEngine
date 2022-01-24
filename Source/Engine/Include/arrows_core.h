/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#ifndef ARROWSAPI
#  define ARROWSAPI extern
#endif

#include <arrows_math.h>
#include <memory>

#define arroptr             std::shared_ptr
#define make_arroptr        std::make_shared
#define ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))

#define GET_SHADER(name) "../../../Source/Engine/Shaders/"#name