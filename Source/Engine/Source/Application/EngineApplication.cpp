/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "EngineApplication.h"

#include <RHI.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <ctime>

#include "Camera/Camera.hpp"

void SetUpImGui(ANCI_WINDOW_HANDLE h)
{
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *) h, true);
        ImGui_ImplOpenGL3_Init("#version 410");
}

void F_ResizeCallback(RHIWindow window, int w, int h)
{
        RHIViewport(0, 0, w, h);
}

EngineApplication::EngineApplication()
{
        /* 初始化RHI函数 */
        RHIProcAddressInit(OpenGL);

        _window = make_anciptr<EngineWindow>("暗刺引擎", 800, 800);
        RHISetWindowResizeCallback(_window->GetHandle(), F_ResizeCallback);

        SetUpImGui(_window->GetHandle());
}

struct RHIVtxBufferArray {
        ancivec3 pos;
        ancivec2 uv;
        ancivec3 color;
        ancivec3 normal;
};

void EngineApplication::StartEngine()
{

        RHIVtxBufferArray vertices[] = {
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
                {{0.5f,  -0.5f, -0.5f}, {1.0f, 0.0f,}},
                {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f,}},
                {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f,}},
                {{-0.5f, 0.5f,  -0.5f}, {0.0f, 1.0f,}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f,}},
                {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f,}},
                {{0.5f,  -0.5f, 0.5f},  {1.0f, 0.0f,}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f,}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f,}},
                {{-0.5f, 0.5f,  0.5f},  {0.0f, 1.0f,}},
                {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f,}},
                {{-0.5f, 0.5f,  0.5f},  {1.0f, 0.0f,}},
                {{-0.5f, 0.5f,  -0.5f}, {1.0f, 1.0f,}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f,}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f,}},
                {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f,}},
                {{-0.5f, 0.5f,  0.5f},  {1.0f, 0.0f,}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f,}},
                {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f,}},
                {{0.5f,  -0.5f, -0.5f}, {0.0f, 1.0f,}},
                {{0.5f,  -0.5f, -0.5f}, {0.0f, 1.0f,}},
                {{0.5f,  -0.5f, 0.5f},  {0.0f, 0.0f,}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f,}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f,}},
                {{0.5f,  -0.5f, -0.5f}, {1.0f, 1.0f,}},
                {{0.5f,  -0.5f, 0.5f},  {1.0f, 0.0f,}},
                {{0.5f,  -0.5f, 0.5f},  {1.0f, 0.0f,}},
                {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f,}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f,}},
                {{-0.5f, 0.5f,  -0.5f}, {0.0f, 1.0f,}},
                {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f,}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f,}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f,}},
                {{-0.5f, 0.5f,  0.5f},  {0.0f, 0.0f,}},
                {{-0.5f, 0.5f,  -0.5f}, {0.0f, 1.0f,}}
        };

        RHIVtxBufferLayout layouts[] = {
                {0, 3, RHI_FLOAT, offsetof(RHIVtxBufferArray, pos)},
                {1, 2, RHI_FLOAT, offsetof(RHIVtxBufferArray, uv)},
                {2, 3, RHI_FLOAT, offsetof(RHIVtxBufferArray, color)},
                {3, 3, RHI_FLOAT, offsetof(RHIVtxBufferArray, normal)},
        };

        RHIVtxBufferCreateInfo vtxBufferCreateInfo = {};
        vtxBufferCreateInfo.vertexCount = ARRAY_SIZE(vertices);
        vtxBufferCreateInfo.stride = sizeof(RHIVtxBufferArray);
        vtxBufferCreateInfo.pBufferLayout = layouts;
        vtxBufferCreateInfo.bufferLayoutCount = ARRAY_SIZE(layouts);

        RHIVtxBuffer vtxBuffer = RHIGenVtxBuffer(vertices, &vtxBufferCreateInfo);

        anciu32 indices[] = {
                0, 1, 3,
                1, 2, 3
        };
        RHIIdxBuffer idxBuffer = RHIGenIdxBuffer(indices, ARRAY_SIZE(indices));

        RHIShader shader = RHICreateShader("../../../Source/Engine/Shaders/simple.alsl");

        int width, height, ns;
        stbi_set_flip_vertically_on_load(true);
        anciuc *pixels = stbi_load("../../../Assets/container.jpg", &width, &height, &ns, 0);
        if (!pixels)
                throw std::runtime_error("加载纹理失败。");

        RHITextureCreateInfo textureCreateInfo0 = {};
        textureCreateInfo0.format = RHI_IMAGE_FORMAT_RGB;
        textureCreateInfo0.width = width;
        textureCreateInfo0.height = height;
        textureCreateInfo0.pPixels = pixels;
        textureCreateInfo0.textureWrapU = RHI_TEXTURE_WRAP_REPEAT;
        textureCreateInfo0.textureWrapV = RHI_TEXTURE_WRAP_REPEAT;
        textureCreateInfo0.textureFilterMin = RHI_TEXTURE_FILTER_NEAREST;
        textureCreateInfo0.textureFilterMag = RHI_TEXTURE_FILTER_NEAREST;

        RHITexture texture0 = RHIGenTexture(&textureCreateInfo0);
        stbi_image_free(pixels);

        pixels = stbi_load("../../../Assets/awesomeface.png", &width, &height, &ns, 0);
        if (!pixels)
                throw std::runtime_error("加载纹理失败。");

        RHITextureCreateInfo textureCreateInfo1 = {};
        textureCreateInfo1.format = RHI_IMAGE_FORMAT_RGBA;
        textureCreateInfo1.width = width;
        textureCreateInfo1.height = height;
        textureCreateInfo1.pPixels = pixels;
        textureCreateInfo1.textureWrapU = RHI_TEXTURE_WRAP_REPEAT;
        textureCreateInfo1.textureWrapV = RHI_TEXTURE_WRAP_REPEAT;
        textureCreateInfo1.textureFilterMin = RHI_TEXTURE_FILTER_NEAREST;
        textureCreateInfo1.textureFilterMag = RHI_TEXTURE_FILTER_NEAREST;

        RHITexture texture1 = RHIGenTexture(&textureCreateInfo1);
        stbi_image_free(pixels);

        RHIBindShader(shader);
        RHIUniform1i(shader, "ourSampler2D_0", 0);
        RHIUniform1i(shader, "ourSampler2D_1", 1);

        bool show_demo_window = false;
        float zNear = 0.01f, zFar = 100.0f, degrees = 45.0f;
        float rotateDegrees = -55.0f;
        ancivec3 rotateXZY(1.0f, 0.0f, 0.0f);
        ancibool isEnableDepthTest = RHI_TRUE;
        clock_t renderTime;

        ancivec3 cubePositions[] = {
                glm::vec3( 0.0f,  0.0f,  0.0f),
                glm::vec3( 2.0f,  5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3( 2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f,  3.0f, -7.5f),
                glm::vec3( 1.3f, -2.0f, -2.5f),
                glm::vec3( 1.5f,  2.0f, -2.5f),
                glm::vec3( 1.5f,  0.2f, -1.5f),
                glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        Camera camera{};

        float deltaTime = 0.0f;
        float lastTime  = 0.0f;

        while (!_window->ShouldClose()) {
                _window->PollEvents();

                float currentFrame = RHIGetTime();
                deltaTime = currentFrame - lastTime;
                lastTime = currentFrame;

                clock_t renderStartTime;
                renderStartTime = clock();

                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                if (show_demo_window)
                        ImGui::ShowDemoWindow(&show_demo_window);

                RHIClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);
                RHIEnable(RHI_DEPTH_TEST, isEnableDepthTest);

                if (ImGui::Begin("Debug")) {
                        ImGui::Text("ZNear");
                        ImGui::SameLine();
                        ImGui::DragFloat("zNear", &zNear, 0.1f);

                        ImGui::Text("zFar");
                        ImGui::SameLine();
                        ImGui::DragFloat("zFar", &zFar, 1.0f);

                        ImGui::Text("degrees");
                        ImGui::SameLine();
                        ImGui::DragFloat("degrees", &degrees, 1.0f);

                        ImGui::Text("rotateDegrees");
                        ImGui::SameLine();
                        ImGui::DragFloat("rotateDegrees", &rotateDegrees, 1.0f);

                        ImGui::Text("rotateXZY");
                        ImGui::SameLine();
                        ImGui::DragFloat3("rotateXZY", glm::value_ptr(rotateXZY), 0.01f);

                        if (ImGui::Button("EnableDepthTest")) {
                                isEnableDepthTest = !isEnableDepthTest;
                        } ImGui::SameLine(); ImGui::Text("%d", isEnableDepthTest);
                } ImGui::End();

                if (ImGui::Begin("Performance")) {
                        ImGui::Text("RenderTime: %ldms", renderTime);
                } ImGui::End();

                RHIBindTexture(texture0);
                RHIBindTexture(texture1);
                RHIBindVtxBuffer(vtxBuffer);

                camera.Update(_window->GetHandle(), deltaTime);

                for (ancivec3 pos : cubePositions) {
                        ancimat4 model{1.0f};
                        ancimat4 projection{1.0f};
                        ancimat4 view{1.0f};
                        model = glm::rotate(model, glm::radians(rotateDegrees), rotateXZY);
                        model = glm::translate(model, pos);

                        RHIDimension dimension = _window->GetDimension();
                        projection = glm::perspective(glm::radians(degrees), (float) dimension.x / (float) dimension.y, zNear, zFar);

                        ancimat4 viewMatrix = camera.GetViewMatrix();
                        RHIUniformMatrix4fv(shader, "model", glm::value_ptr(model));
                        RHIUniformMatrix4fv(shader, "view", glm::value_ptr(viewMatrix));
                        RHIUniformMatrix4fv(shader, "proj", glm::value_ptr(projection));

                        RHIDrawVtx(0, 36);
                }

                // Rendering
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                ImGuiIO &io = ImGui::GetIO();
                if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                {
                        RHIWindow backup_current_context = RHIGetCurrentContext_GL();
                        ImGui::UpdatePlatformWindows();
                        ImGui::RenderPlatformWindowsDefault();
                        RHIMakeContextCurrent_GL(backup_current_context);
                }

                RHISwapBuffers(_window->GetHandle());

                renderTime = clock() - renderStartTime;
        }

        RHIDeleteShader(shader);
        RHIDeleteTexture(texture0);
        RHIDeleteTexture(texture1);
        RHIDeleteVtxBuffer(vtxBuffer);
        RHIDeleteVtxBuffer(idxBuffer);
}