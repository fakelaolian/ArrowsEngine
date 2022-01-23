CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(AnciEngine)

SET(CMAKE_CXX_STANDARD 23)

INCLUDE_DIRECTORIES(${PROJECT_NAME} Source)
INCLUDE_DIRECTORIES(${PROJECT_NAME} SYSTEM
        Include
        ThirdParty
        ThirdParty/glfw3/include
        ThirdParty/glad/include
        ThirdParty/imgui)

LINK_LIBRARIES(imm32)
LINK_DIRECTORIES(${PROJECT_NAME} ThirdParty/glfw3/lib-mingw-w64)
ADD_EXECUTABLE(${PROJECT_NAME}
        Source/Main/main.cpp
        # --* Application *-- #
        Source/Application/AnciWindow.cpp
        Source/Application/AnciApplication.cpp
        # --* GUI *-- #
        Source/ImGui/AnciGUI.cpp
        # --* Scene *-- #
        Source/Scene/Scene.cpp
        Source/Scene/GameObject.cpp
        Source/Scene/SceneCamera.cpp
        Source/Scene/SkyBox.cpp
        # --* Loader *-- #
        Source/Loader/TextureLoader.cpp
        Source/Loader/ModelLoader.cpp
        # --* ThirdParty/glad *-- #
        ThirdParty/glad/src/glad.c
        # --* ThirdParty/ImGui *-- #
        ThirdParty/imgui/imgui.cpp
        ThirdParty/imgui/imgui_tables.cpp
        ThirdParty/imgui/imgui_demo.cpp
        ThirdParty/imgui/imgui_draw.cpp
        ThirdParty/imgui/imgui_widgets.cpp
        ThirdParty/imgui/backends/imgui_impl_opengl3.cpp
        ThirdParty/imgui/backends/imgui_impl_glfw.cpp

)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} glfw3 RHI)
