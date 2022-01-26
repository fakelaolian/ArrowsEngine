CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(Ars C)

SET(CMAKE_C_STANDARD 11)

INCLUDE_DIRECTORIES(${PROJECT_NAME} include)
INCLUDE_DIRECTORIES(${PROJECT_NAME} SYSTEM third/glfw3/include third/glad/include)

LINK_DIRECTORIES(third)
ADD_LIBRARY(${PROJECT_NAME} STATIC
        third/glad/src/glad.c
        source/alsl.c
        source/glfw.c
        source/load_proc_functions.c
        source/impl_opengl.c
)