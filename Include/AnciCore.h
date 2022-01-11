/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#ifndef ANCIAPI
#  define ANCIAPI extern
#endif

#ifndef ANCI_WINDOW_HANDLE
#  define ANCI_WINDOW_HANDLE void *
#endif

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef String
#  include <string>
#  define String std::string
#endif

/* 图形API选择枚举 */
enum AnciEnumGraphicsApi {
        Vulkan,
        OpenGL,
        DX12
};

typedef unsigned char       anciuc;
typedef unsigned int        anciu32;
typedef unsigned long       anciu64;
typedef glm::vec2           ancivec2;
typedef glm::vec3           ancivec3;
typedef glm::vec4           ancivec4;
typedef glm::mat2           ancimat2;
typedef glm::mat3           ancimat3;
typedef glm::mat4           ancimat4;
#define anciptr             std::shared_ptr

#define make_anciptr        std::make_shared
#define ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))