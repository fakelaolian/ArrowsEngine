/* AUTHOR: BlazeStark, DATE: 2022/1/6 */
#pragma once

#ifndef ANCIAPI
#  define ANCIAPI extern
#endif

#include <memory>
#include <glm/glm.hpp>

#ifndef String
#  include <string>
   typedef std::string      String;
#endif

/* 图形API选择枚举 */
enum AnciEnumGraphicsApi {
        Vulkan,
        OpenGL,
        DX12
};

typedef unsigned            anciu32;
typedef unsigned long       anciu64;
typedef glm::vec2           ancivec2;
typedef glm::vec3           ancivec3;
typedef glm::vec4           ancivec4;
#define anciptr             std::unique_ptr