CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(AnciEngine)

SET(CMAKE_CXX_STANDARD 23)

INCLUDE_DIRECTORIES(${PROJECT_NAME} Engine/Source)
INCLUDE_DIRECTORIES(${PROJECT_NAME} SYSTEM
        Engine/Include
        Engine/ThirdParty
        Engine/ThirdParty/glfw3/include
        Engine/ThirdParty/glad/include
        Engine/ThirdParty/imgui)

LINK_LIBRARIES(imm32)
LINK_DIRECTORIES(${PROJECT_NAME} Engine/ThirdParty/glfw3/lib-mingw-w64)
ADD_EXECUTABLE(${PROJECT_NAME}
        Engine/Source/Main/main.cpp
        # --* Tools *-- #
        Engine/Source/Tools/AnciCreator.cpp
        # --* Application *-- #
        Engine/Source/Application/EngineApplication.cpp
        # --* Alsl *-- #
        Engine/Source/Alsl/Alsl.cpp
        # --* Platform/OpenGL *-- #
        Engine/Source/Platform/OpenGL/OpenGLWindow.cpp
        Engine/Source/Platform/OpenGL/OpenGLShader.cpp
        Engine/Source/Platform/OpenGL/RHI_ImplOpenGL.cpp
        # --* ThirdParty/glad *-- #
        Engine/ThirdParty/glad/src/glad.c
        # --* ThirdParty/ImGui *-- #
        Engine/ThirdParty/imgui/imgui.cpp
        Engine/ThirdParty/imgui/imgui_tables.cpp
        Engine/ThirdParty/imgui/imgui_demo.cpp
        Engine/ThirdParty/imgui/imgui_draw.cpp
        Engine/ThirdParty/imgui/imgui_widgets.cpp
        Engine/ThirdParty/imgui/backends/imgui_impl_opengl3.cpp
        Engine/ThirdParty/imgui/backends/imgui_impl_glfw.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} glfw3)
