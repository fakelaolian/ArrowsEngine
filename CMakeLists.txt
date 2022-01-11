CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(AnciEngine)

SET(CMAKE_CXX_STANDARD 23)

INCLUDE_DIRECTORIES(${PROJECT_NAME} Engine)
INCLUDE_DIRECTORIES(${PROJECT_NAME} SYSTEM
        Include
        ThirdParty
        ThirdParty/glfw3/include
        ThirdParty/glad/include
        ThirdParty/imgui
)

LINK_LIBRARIES(imm32)
LINK_DIRECTORIES(${PROJECT_NAME} ThirdParty/glfw3/lib-mingw-w64)
ADD_EXECUTABLE(${PROJECT_NAME}
        Engine/Main/main.cpp
        ThirdParty/glad/src/glad.c
        # --* Tools *-- #
        Engine/Tools/AnciCreator.cpp
        # --* Application *-- #
        Engine/Application/EngineApplication.cpp
        # --* Alsl *-- #
        Engine/Alsl/Alsl.cpp
        # --* Platform/OpenGL *-- #
        Engine/Platform/OpenGL/OpenGLWindow.cpp
        Engine/Platform/OpenGL/OpenGLShader.cpp
        Engine/Platform/OpenGL/RHI_ImplOpenGL.cpp
        # --* ThirdParty/ImGui *-- #
        ThirdParty/imgui/imgui.cpp
        ThirdParty/imgui/imgui_tables.cpp
        ThirdParty/imgui/imgui_demo.cpp
        ThirdParty/imgui/imgui_draw.cpp
        ThirdParty/imgui/imgui_widgets.cpp
        ThirdParty/imgui/backends/imgui_impl_opengl3.cpp
        ThirdParty/imgui/backends/imgui_impl_glfw.cpp
)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} glfw3)
