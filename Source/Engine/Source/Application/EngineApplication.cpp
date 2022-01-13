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
        ancivec3 color;
        ancivec3 normal;
};

bool isShowCursor = true;
bool firstMouse = true;
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

        RHIDimension2f cursor = window.GetCursor();
        float xpos = static_cast<float>(cursor.x);
        float ypos = static_cast<float>(cursor.y);

        if (firstMouse)
        {
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

clock_t renderTime;
void UpdateImGui()
{
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::Begin("Performance")) {
                ImGui::Text("RenderTime: %ldms", renderTime);
        } ImGui::End();

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

void UpdateMVPMatrix(EngineWindow &engineWindow, Camera &camera, RHIShader shader, ancivec3 modelPos)
{
        ancimat4 model{1.0f};
        ancimat4 projection{1.0f};
        ancimat4 view{1.0f};
        model = glm::rotate(model, glm::radians(-55.0f), ancivec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, modelPos);

        RHIDimension2i dimension = engineWindow.GetDimension();
        projection = glm::perspective(glm::radians(45.0f), (float) dimension.x / (float) dimension.y, 0.01f, 100.0f);

        ancimat4 viewMatrix = camera.GetViewMatrix();
        RHIUniformMatrix4fv(shader, "model", glm::value_ptr(model));
        RHIUniformMatrix4fv(shader, "view", glm::value_ptr(viewMatrix));
        RHIUniformMatrix4fv(shader, "proj", glm::value_ptr(projection));
}

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
        RHIShader colorShader = RHICreateShader("../../../Source/Engine/Shaders/color.alsl");
        RHIShader lightShader = RHICreateShader("../../../Source/Engine/Shaders/light.alsl");
        Camera camera{};

        float deltaTime = 0.0f;
        float lastTime  = 0.0f;

        ancivec3 objectColor{1.0f, 0.5f, 0.31f};
        ancivec3 lightColor{1.0f, 1.0f, 1.0f};

        RHIEnable(RHI_DEPTH_TEST, RHI_TRUE);
        while (!_window->ShouldClose()) {
                _window->PollEvents();

                float currentFrame = RHIGetTime();
                deltaTime = currentFrame - lastTime;
                lastTime = currentFrame;

                clock_t renderStartTime;
                renderStartTime = clock();

                RHIClearColorBuffer(0.0f, 0.0f, 0.0f, 0.0f);

                UpdateImGui();
                UpdateCamera(*_window, camera, deltaTime);

                RHIBindShader(colorShader);
                RHIBindVtxBuffer(vtxBuffer);
                UpdateMVPMatrix(*_window, camera, colorShader, {0.0f, 0.0f, -1.0f});
                RHIUniform3fv(colorShader, "objectColor", glm::value_ptr(objectColor));
                RHIUniform3fv(lightShader, "lightColor", glm::value_ptr(lightColor));
                RHIDrawVtx(0, 36);

                RHIBindShader(lightShader);
                RHIBindVtxBuffer(vtxBuffer);
                UpdateMVPMatrix(*_window, camera, lightShader, {3.0f, 0.0f, -1.0f});
                RHIUniform3fv(lightShader, "lightColor", glm::value_ptr(lightColor));
                RHIDrawVtx(0, 36);

                RHISwapBuffers(_window->GetHandle());
                renderTime = clock() - renderStartTime;
        }
}