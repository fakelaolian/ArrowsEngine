/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "EngineApplication.h"

#include <RHI.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <ctime>
#include <vector>

#include <glad/glad.h>

#include "Camera/Camera.hpp"

void SetUpImGui(RHIWindow h)
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

EngineApplication::EngineApplication()
{
        /* 初始化RHI函数 */
        RHIProcAddressInit(OpenGL);

        _window = make_anciptr<EngineWindow>("暗刺引擎", 800, 800);

        SetUpImGui(_window->GetHandle());
}

struct RHIVtxBufferArray {
        ancivec3 pos;
        ancivec2 uv;
        ancivec3 normal;
        ancivec3 color;
};

bool isShowCursor = true;
bool firstMouse = true;
bool isEnableMouseMove = false;
float lastX, lastY;
void UpdateCamera(EngineWindow &window, Camera& camera, float deltaTime)
{
        if (RHIGetKey(window.GetHandle(), RHI_KEY_ESCAPE) == RHI_PRESS) {
                isShowCursor = !isShowCursor;
                !isShowCursor ? RHISetCursorMode(window.GetHandle(), RHI_CURSOR_DISABLE) :
                RHISetCursorMode(window.GetHandle(), RHI_CURSOR_NORMAL);
        }

        /* 更新相机数据 */
        if (RHIGetKey(window.GetHandle(), RHI_KEY_W) == RHI_PRESS)
                camera.ProcessKeyboard(FORWARD, deltaTime);
        if (RHIGetKey(window.GetHandle(), RHI_KEY_S) == RHI_PRESS)
                camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (RHIGetKey(window.GetHandle(), RHI_KEY_A) == RHI_PRESS)
                camera.ProcessKeyboard(LEFT, deltaTime);
        if (RHIGetKey(window.GetHandle(), RHI_KEY_D) == RHI_PRESS)
                camera.ProcessKeyboard(RIGHT, deltaTime);
        if (RHIGetKey(window.GetHandle(), RHI_KEY_Q) == RHI_PRESS)
                camera.ProcessKeyboard(UP, deltaTime);
        if (RHIGetKey(window.GetHandle(), RHI_KEY_E) == RHI_PRESS)
                camera.ProcessKeyboard(DOWN, deltaTime);

        if (RHIGetKey(window.GetHandle(), RHI_KEY_TAB) == RHI_PRESS)
                isEnableMouseMove = !isEnableMouseMove;

        if (isEnableMouseMove) {
                RHIDimension2f cursor = window.GetCursor();
                auto xpos = static_cast<float>(cursor.x);
                auto ypos = static_cast<float>(cursor.y);

                if (firstMouse) {
                        lastX = xpos;
                        lastY = ypos;
                        firstMouse = false;
                }

                float xoffset = xpos - lastX;
                float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

                lastX = xpos;
                lastY = ypos;

                camera.ProcessMouseMovement(xoffset, yoffset);
        }
}

void BeginImGui()
{
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
}

void EndImGui()
{
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
}

void LoadCubeMap(RHITexture *cubeTexture)
{
        ////////////////////////////////////////////////////////////
        ////////                   天空盒                    ////////
        ////////////////////////////////////////////////////////////
        std::vector<const char *> skyboxsImage = {
                "../../../Assets/skyboxs/a/right.jpg",
                "../../../Assets/skyboxs/a/left.jpg",
                "../../../Assets/skyboxs/a/top.jpg",
                "../../../Assets/skyboxs/a/bottom.jpg",
                "../../../Assets/skyboxs/a/front.jpg",
                "../../../Assets/skyboxs/a/back.jpg",
        };

        RHITextureCubeCreateInfo skyboxCreateInfo = {};
        skyboxCreateInfo.textureFilterMin = RHI_TEXTURE_FILTER_LINEAR;
        skyboxCreateInfo.textureFilterMag = RHI_TEXTURE_FILTER_LINEAR;
        skyboxCreateInfo.textureWrapS = RHI_TEXTURE_WRAP_CLAMP_TO_EDGE;
        skyboxCreateInfo.textureWrapT = RHI_TEXTURE_WRAP_CLAMP_TO_EDGE;
        skyboxCreateInfo.textureWrapR = RHI_TEXTURE_WRAP_CLAMP_TO_EDGE;

        int w = 0, h = 0, nr = 0;
        for (anciu32 i = 0; i < skyboxsImage.size(); i++) {
                anciuc *pixels = stbi_load(skyboxsImage[i], &w, &h, &nr, 0);

                skyboxCreateInfo.format[i] = RHI_IMAGE_FORMAT_RGB;
                skyboxCreateInfo.pPixels[i] = pixels;
                skyboxCreateInfo.width[i] = w;
                skyboxCreateInfo.height[i] = h;
        }

        *cubeTexture = RHIGenTextureCubeMap(&skyboxCreateInfo);

        for (auto p_data : skyboxCreateInfo.pPixels) {
                stbi_image_free(p_data);
        }

}

void EngineApplication::StartEngine()
{
        RHIVtxBufferArray vertices[] = {
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f},  {0.0f,  0.0f,  -1.0f}},
                {{0.5f,  -0.5f, -0.5f}, {1.0f, 0.0f,}, {0.0f,  0.0f,  -1.0f}},
                {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f,}, {0.0f,  0.0f,  -1.0f}},
                {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f,}, {0.0f,  0.0f,  -1.0f}},
                {{-0.5f, 0.5f,  -0.5f}, {0.0f, 1.0f,}, {0.0f,  0.0f,  -1.0f}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f,}, {0.0f,  0.0f,  -1.0f}},
                {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f,}, {0.0f,  0.0f,  1.0f}},
                {{0.5f,  -0.5f, 0.5f},  {1.0f, 0.0f,}, {0.0f,  0.0f,  1.0f}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f,}, {0.0f,  0.0f,  1.0f}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f,}, {0.0f,  0.0f,  1.0f}},
                {{-0.5f, 0.5f,  0.5f},  {0.0f, 1.0f,}, {0.0f,  0.0f,  1.0f}},
                {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f,}, {0.0f,  0.0f,  1.0f}},
                {{-0.5f, 0.5f,  0.5f},  {1.0f, 0.0f,}, {-1.0f, 0.0f,  0.0f}},
                {{-0.5f, 0.5f,  -0.5f}, {1.0f, 1.0f,}, {-1.0f, 0.0f,  0.0f}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f,}, {-1.0f, 0.0f,  0.0f}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f,}, {-1.0f, 0.0f,  0.0f}},
                {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f,}, {-1.0f, 0.0f,  0.0f}},
                {{-0.5f, 0.5f,  0.5f},  {1.0f, 0.0f,}, {-1.0f, 0.0f,  0.0f}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f,}, {1.0f,  0.0f,  0.0f}},
                {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f,}, {1.0f,  0.0f,  0.0f}},
                {{0.5f,  -0.5f, -0.5f}, {0.0f, 1.0f,}, {1.0f,  0.0f,  0.0f}},
                {{0.5f,  -0.5f, -0.5f}, {0.0f, 1.0f,}, {1.0f,  0.0f,  0.0f}},
                {{0.5f,  -0.5f, 0.5f},  {0.0f, 0.0f,}, {1.0f,  0.0f,  0.0f}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f,}, {1.0f,  0.0f,  0.0f}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f,}, {0.0f,  -1.0f, 0.0f}},
                {{0.5f,  -0.5f, -0.5f}, {1.0f, 1.0f,}, {0.0f,  -1.0f, 0.0f}},
                {{0.5f,  -0.5f, 0.5f},  {1.0f, 0.0f,}, {0.0f,  -1.0f, 0.0f}},
                {{0.5f,  -0.5f, 0.5f},  {1.0f, 0.0f,}, {0.0f,  -1.0f, 0.0f}},
                {{-0.5f, -0.5f, 0.5f},  {0.0f, 0.0f,}, {0.0f,  -1.0f, 0.0f}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f,}, {0.0f,  -1.0f, 0.0f}},
                {{-0.5f, 0.5f,  -0.5f}, {0.0f, 1.0f,}, {0.0f,  1.0f,  0.0f}},
                {{0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f,}, {0.0f,  1.0f,  0.0f}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f,}, {0.0f,  1.0f,  0.0f}},
                {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f,}, {0.0f,  1.0f,  0.0f}},
                {{-0.5f, 0.5f,  0.5f},  {0.0f, 0.0f,}, {0.0f,  1.0f,  0.0f}},
                {{-0.5f, 0.5f,  -0.5f}, {0.0f, 1.0f,}, {0.0f,  1.0f,  0.0f}}
        };

        RHIVtxBufferLayout layouts[] = {
                {0, 3, RHI_FLOAT, offsetof(RHIVtxBufferArray, pos)},
                {1, 2, RHI_FLOAT, offsetof(RHIVtxBufferArray, uv)},
                {2, 3, RHI_FLOAT, offsetof(RHIVtxBufferArray, normal)},
                {3, 3, RHI_FLOAT, offsetof(RHIVtxBufferArray, color)},
        };

        RHIVtxBufferCreateInfo vtxBufferCreateInfo = {};
        vtxBufferCreateInfo.vertexCount = ARRAY_SIZE(vertices);
        vtxBufferCreateInfo.stride = sizeof(RHIVtxBufferArray);
        vtxBufferCreateInfo.pBufferLayout = layouts;
        vtxBufferCreateInfo.bufferLayoutCount = ARRAY_SIZE(layouts);

        RHIVtxBuffer cubeVtxBuffer = RHIGenVtxBuffer(vertices, &vtxBufferCreateInfo);

        RHIShader cubeShader = RHICreateShader("../../../Source/Engine/Shaders/cube.alsl");
        RHIShader skyboxShader = RHICreateShader("../../../Source/Engine/Shaders/skyboxs.alsl");

        int width, height, nc;
        anciuc *pixels = stbi_load("../../../Assets/container2.png", &width, &height, &nc, 0);

        RHITexture2DCreateInfo textureCreateInfo = {};
        textureCreateInfo.pPixels = pixels;
        textureCreateInfo.width = width;
        textureCreateInfo.height = height;
        textureCreateInfo.format = RHI_IMAGE_FORMAT_RGBA;
        textureCreateInfo.textureWrapS = RHI_TEXTURE_WRAP_REPEAT;
        textureCreateInfo.textureWrapT = RHI_TEXTURE_WRAP_REPEAT;
        textureCreateInfo.textureFilterMin = RHI_TEXTURE_FILTER_LINEAR;
        textureCreateInfo.textureFilterMag = RHI_TEXTURE_FILTER_LINEAR;

        RHITexture cubeTexture = RHIGenTexture2D(&textureCreateInfo);

        stbi_image_free(pixels);

        /* 加载天空盒 */
        RHIVtxBufferArray skyboxArray[] = {
                {{-1.0f,  1.0f, -1.0f}},
                {{-1.0f, -1.0f, -1.0f}},
                {{1.0f, -1.0f, -1.0f}},
                {{1.0f, -1.0f, -1.0f}},
                {{1.0f,  1.0f, -1.0f}},
                {{-1.0f,  1.0f, -1.0f}},
                {{-1.0f, -1.0f,  1.0f}},
                {{-1.0f, -1.0f, -1.0f}},
                {{-1.0f,  1.0f, -1.0f}},
                {{-1.0f,  1.0f, -1.0f}},
                {{-1.0f,  1.0f,  1.0f}},
                {{-1.0f, -1.0f,  1.0f}},
                {{1.0f, -1.0f, -1.0f}},
                {{1.0f, -1.0f,  1.0f}},
                {{1.0f,  1.0f,  1.0f}},
                {{1.0f,  1.0f,  1.0f}},
                {{1.0f,  1.0f, -1.0f}},
                {{1.0f, -1.0f, -1.0f}},
                {{-1.0f, -1.0f,  1.0f}},
                {{-1.0f,  1.0f,  1.0f}},
                {{1.0f,  1.0f,  1.0f}},
                {{1.0f,  1.0f,  1.0f}},
                {{1.0f, -1.0f,  1.0f}},
                {{-1.0f, -1.0f,  1.0f}},
                {{-1.0f,  1.0f, -1.0f}},
                {{1.0f,  1.0f, -1.0f}},
                {{1.0f,  1.0f,  1.0f}},
                {{1.0f,  1.0f,  1.0f}},
                {{-1.0f,  1.0f,  1.0f}},
                {{-1.0f,  1.0f, -1.0f}},
                {{-1.0f, -1.0f, -1.0f}},
                {{-1.0f, -1.0f,  1.0f}},
                {{1.0f, -1.0f, -1.0f}},
                {{1.0f, -1.0f, -1.0f}},
                {{-1.0f, -1.0f,  1.0f}},
                {{1.0f, -1.0f,  1.0f}}
        };
        RHIVtxBuffer skyboxBufArray = RHIGenVtxBuffer(skyboxArray, &vtxBufferCreateInfo);

        RHITexture skyboxTexture;
        LoadCubeMap(&skyboxTexture);

        Camera camera{{-0.747, 1.247, 4.816}};

        float deltaTime = 0.0f;
        float lastTime  = 0.0f;

        RHIBindShader(cubeShader);
        RHIUniform1i(cubeShader, "cubeTexture", 0);
        RHIBindShader(skyboxShader);
        RHIUniform1i(skyboxShader, "skybox", 0);

        ancivec3 skyboxScale{1.0f};
        float skyboxScalefv = 1.0f;
        float skyBoxRotate = -55.0f;

        clock_t renderTime;
        clock_t beginTime;

        RHIEnable(RHI_DEPTH_TEST, RHI_TRUE);
        while (!_window->ShouldClose()) {
                _window->PollEvents();
                RHIClearColorBuffer(0.0f, 0.0f, 0.0f, 0.0f);

                float currentFrame = RHIGetTime();
                deltaTime = currentFrame - lastTime;
                lastTime = currentFrame;
                beginTime = clock();

                UpdateCamera(*_window, camera, deltaTime);

                ancimat4 model{1.0f};
                model = glm::rotate(model, glm::radians(-55.0f), {0.0f, 0.0f, -3.0f});
                model = glm::translate(model, {1.0f, 1.0f, 1.0f});
                ancimat4 projection{1.0f};
                ancimat4 view{1.0f};
                RHIDimension2i dimension = _window->GetDimension();
                projection = glm::perspective(glm::radians(45.0f), (float) dimension.x / (float) dimension.y, 0.01f, 100.0f);

                ancimat4 viewMatrix = camera.GetViewMatrix();

                RHIBindShader(cubeShader);
                RHIUniformMatrix4fv(cubeShader, "model", glm::value_ptr(model));
                RHIUniformMatrix4fv(cubeShader, "view", glm::value_ptr(viewMatrix));
                RHIUniformMatrix4fv(cubeShader, "projection", glm::value_ptr(projection));
                RHIBindTexture(RHI_TEXTURE_2D, cubeTexture);
                RHIBindVtxBuffer(cubeVtxBuffer);
                RHIDrawVtx(0, 36);

                RHIDepthOption(RHI_DEPTH_OPTION_LE);
                RHIBindShader(skyboxShader);
                ancimat4 skyboxView = ancimat4(ancimat3(viewMatrix));
                RHIUniformMatrix4fv(cubeShader, "view", glm::value_ptr(skyboxView));
                RHIUniformMatrix4fv(cubeShader, "projection", glm::value_ptr(projection));
                RHIBindTexture(RHI_TEXTURE_CUBE_MAP, skyboxTexture);
                RHIBindVtxBuffer(skyboxBufArray);
                RHIDrawVtx(0, 36);
                RHIDepthOption(RHI_DEPTH_OPTION_LT);

                renderTime = clock() - beginTime;

//                BeginImGui();
//                {
//                        if (ImGui::Begin("Debug")) {
//                                ImGui::DragFloat("skyboxScale", &skyboxScalefv, 1.0f);
//                                skyboxScale.x = skyboxScale.y = skyboxScale.z = skyboxScalefv;
//                                ImGui::DragFloat("skyBoxRotate", &skyBoxRotate, 1.0f);
//
//                                if (ImGui::Begin("Preference")) {
//                                        ImGui::Text("RenderTime: %ldms", renderTime);
//                                } ImGui::End();
//                        } ImGui::End();
//                } EndImGui();

                RHISwapBuffers(_window->GetHandle());
        }
}