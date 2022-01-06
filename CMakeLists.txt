CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(AnciEngine)

SET(CMAKE_CXX_STANDARD 23)

INCLUDE_DIRECTORIES(${PROJECT_NAME} Engine)
INCLUDE_DIRECTORIES(${PROJECT_NAME} SYSTEM Include ThirdParty ThirdParty/glfw3/include ThirdParty/glad/include)

LINK_DIRECTORIES(ThirdParty/glfw3/lib-mingw-w64)
ADD_EXECUTABLE(${PROJECT_NAME}
        Engine/Main/main.cpp
        ThirdParty/glad/src/glad.c
        Engine/Tools/AnciCreator.cpp
        Engine/Application/EngineApplication.cpp
        # --* Platform/OpenGL *-- #
        Engine/Platform/OpenGL/OpenGLWindow.cpp
)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} glfw3)
