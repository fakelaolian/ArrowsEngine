CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
PROJECT(ArrowsEngine)

SET(CMAKE_CXX_STANDARD 23)

INCLUDE_DIRECTORIES(${PROJECT_NAME} Source)
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
        Source/Main/main.cpp
        # --* Application *-- #
        Source/Application/MainWindow.cpp
        Source/Application/MainApplication.cpp
        # --* GUI *-- #
        Source/ImGui/APPGUI.cpp
        Source/ImGui/GUIKIT.cpp
        # --* Scene *-- #
        Source/Scene/Scene.cpp
        Source/Scene/SceneCamera.cpp
        # --* Component *-- #
        Source/Scene/Component/Private/GameObject.cpp
        Source/Scene/Component/Private/GameMesh.cpp
        Source/Scene/Component/Private/SkyBox.cpp
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
        # --* ThirdParty/ImGui/blueprint *-- #
        ThirdParty/imgui/blueprint/imnodes.cpp
        )

TARGET_LINK_LIBRARIES(${PROJECT_NAME} glfw3 Ars)
