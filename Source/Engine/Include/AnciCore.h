/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#ifndef ANCIAPI
#  define ANCIAPI extern
#endif

#include <AnciMath.h>

#include <memory>

typedef unsigned char       anciuc;
typedef unsigned int        anciu32;
typedef unsigned long       anciu64;
#define anciptr             std::shared_ptr

#define make_anciptr        std::make_shared
#define ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))