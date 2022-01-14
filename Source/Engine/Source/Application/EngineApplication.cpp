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
                float xpos = static_cast<float>(cursor.x);
                float ypos = static_cast<float>(cursor.y);

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

clock_t renderTime;
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

        RHIVtxBuffer vtxBuffer = RHIGenVtxBuffer(vertices, &vtxBufferCreateInfo);

        RHIShader lightShader = RHICreateShader("../../../Source/Engine/Shaders/color.alsl");
        RHIShader lightCubeShader = RHICreateShader("../../../Source/Engine/Shaders/light.alsl");

        int width, height, nc;
        anciuc *pixels = stbi_load("../../../Assets/container2.png", &width, &height, &nc, 0);

        RHITextureCreateInfo textureCreateInfo = {};
        textureCreateInfo.pPixels = pixels;
        textureCreateInfo.width = width;
        textureCreateInfo.height = height;
        textureCreateInfo.format = RHI_IMAGE_FORMAT_RGBA;
        textureCreateInfo.textureWrapU = RHI_TEXTURE_WRAP_REPEAT;
        textureCreateInfo.textureWrapV = RHI_TEXTURE_WRAP_REPEAT;
        textureCreateInfo.textureFilterMin = RHI_TEXTURE_FILTER_LINEAR;
        textureCreateInfo.textureFilterMag = RHI_TEXTURE_FILTER_LINEAR;

        RHITexture texture0 = RHIGenTexture(&textureCreateInfo);

        pixels = stbi_load("../../../Assets/container2_specular.png", &width, &height, &nc, 0);

        textureCreateInfo.pPixels = pixels;
        textureCreateInfo.width = width;
        textureCreateInfo.height = height;
        RHITexture texture1 = RHIGenTexture(&textureCreateInfo);

        stbi_image_free(pixels);

        Camera camera{{-0.747, 1.247, 4.816}};

        float deltaTime = 0.0f;
        float lastTime  = 0.0f;

        ancivec3 objectPos{0.0f, 0.0f, -1.0f};
        ancivec3 objectColor{1.0f, 0.5f, 0.31f};

        ancivec3 lightPos{2.590, -0.630, 5.950};
        ancivec3 lightColor{1.0f, 1.0f, 1.0f};

        ancivec3 materialAmbient{1.0f, 0.5f, 0.31f};
        ancivec3 materialDiffuse{1.0f, 0.5f, 0.31f};
        ancivec3 materialSpecular{0.5f, 0.5f, 0.5f};
        float materialShininess{32.0f};

        ancivec3 lightAmbient{0.2f, 0.2f, 0.2f};
        ancivec3 lightDiffuse{0.5f, 0.5f, 0.5f};
        ancivec3 lightSpecular{1.0f, 1.0f, 1.0f};

        RHIEnable(RHI_DEPTH_TEST, RHI_TRUE);
        while (!_window->ShouldClose()) {
                _window->PollEvents();

                float currentFrame = RHIGetTime();
                deltaTime = currentFrame - lastTime;
                lastTime = currentFrame;

                clock_t renderStartTime;
                renderStartTime = clock();

                RHIClearColorBuffer(0.0f, 0.0f, 0.0f, 0.0f);

                BeginImGui();
                {
                        if (ImGui::Begin("Debug")) {
                                ImGui::DragFloat3("LightPosition", glm::value_ptr(lightPos), 0.01f);

                                ImGui::Text("Material");
                                        ImGui::DragFloat3("materialAmbient", glm::value_ptr(materialAmbient), 0.01f);
                                ImGui::DragFloat3("materialDiffuse", glm::value_ptr(materialDiffuse), 0.01f);
                                ImGui::DragFloat3("materialSpecular", glm::value_ptr(materialSpecular), 0.01f);

                                ImGui::Text("Light");
                                ImGui::DragFloat3("lightAmbient", glm::value_ptr(lightAmbient), 0.01f);
                                ImGui::DragFloat3("lightDiffuse", glm::value_ptr(lightDiffuse), 0.01f);
                                ImGui::DragFloat3("lightSpecular", glm::value_ptr(lightSpecular), 0.01f);

                                ImGui::Text("Camera");
                                ImGui::DragFloat3("Position", glm::value_ptr(camera.Position), 0.01f);

                                ImGui::Text("Image");
                                ImGui::Image((void *) (intptr_t) RHIGetTextureId(texture0), ImVec2(64, 64));

                        } ImGui::End();

                        if (ImGui::Begin("Performance")) {
                                ImGui::Text("RenderTime: %ldms", renderTime);
                        } ImGui::End();
                }
                EndImGui();


                UpdateCamera(*_window, camera, deltaTime);

                RHIBindShader(lightShader);
                RHIBindVtxBuffer(vtxBuffer);
                UpdateMVPMatrix(*_window, camera, lightShader, objectPos);
                RHIUniform3fv(lightShader, "objectColor", glm::value_ptr(objectColor));
                RHIUniform3fv(lightShader, "lightPos", glm::value_ptr(lightPos));
                RHIUniform3fv(lightShader, "viewPos", glm::value_ptr(camera.Position));

                // 材质
                RHIUniform1i(lightShader, "materialDiffuse", 0);
                RHIUniform1i(lightShader, "materialSpecular", 1);
                RHIUniform1f(lightShader,  "material.shininess", materialShininess);

                // 光照
                RHIUniform3fv(lightShader, "light.ambient",  glm::value_ptr(lightAmbient));
                RHIUniform3fv(lightShader, "light.diffuse",  glm::value_ptr(lightDiffuse));
                RHIUniform3fv(lightShader, "light.specular", glm::value_ptr(lightSpecular));
                RHIDrawVtx(0, 36);

                RHIBindShader(lightCubeShader);
                RHIBindTexture(texture0);
                RHIBindTexture(texture1);
                RHIBindVtxBuffer(vtxBuffer);

                UpdateMVPMatrix(*_window, camera, lightCubeShader, lightPos);
                RHIUniform3fv(lightCubeShader, "lightColor", glm::value_ptr(lightColor));
                RHIDrawVtx(0, 36);

                RHISwapBuffers(_window->GetHandle());
                renderTime = clock() - renderStartTime;
        }
}