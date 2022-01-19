/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#ifndef ANCIAPI
#  define ANCIAPI extern
#endif

#include <anci_math.h>
#include <memory>

#define anciptr             std::shared_ptr
#define make_anciptr        std::make_shared
#define ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))