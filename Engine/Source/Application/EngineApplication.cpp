/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "EngineApplication.h"

#include <ATools/AnciCreator.h>
#include <RHI/RHI.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GLFW/glfw3.h>

AnciEnumGraphicsApi g_AnciGraphicsApi;

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

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

void FResizeCallback(anciu32 x, anciu32 y)
{
        RHIViewport(0, 0, x, y);
}

EngineApplication::EngineApplication(AnciEnumGraphicsApi api)
{
        g_AnciGraphicsApi = api;
        _window = AnciCreateWindow("暗刺引擎", ancivec2(800, 800));

        _window->SetResizeCallback(FResizeCallback);

        /* 初始化RHI函数 */
        RHIAPIFuncLoad();

        SetUpImGui(_window->GetHandle());
}

void EngineApplication::StartEngine()
{

        RHIVtxArray vertices[] = {
                {{0.5f,  0.5f,  0.0f}, {1.0f, 0.5f, 0.2f}, {1.0f, 1.0f}},
                {{0.5f,  -0.5f, 0.0f}, {1.0f, 0.5f, 0.2f}, {1.0f, 0.0f}},
                {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.5f, 0.2f}, {0.0f, 0.0f}},
                {{-0.5f, 0.5f,  0.0f}, {1.0f, 0.5f, 0.2f}, {0.0f, 1.0f}},
        };

        anciu32 indices[] = {
                0, 1, 3,
                1, 2, 3
        };

        RHIShader shader = RHICreateShader("../Engine/Shaders/simple.alsl");
        RHIVtxBuffer vtxBuffer = RHIGenVtxBuffer(vertices, ARRAY_SIZE(vertices));
        RHIIdxBuffer idxBuffer = RHIGenIdxBuffer(indices, ARRAY_SIZE(indices));

        int width, height, ns;
        stbi_set_flip_vertically_on_load(true);
        anciuc *pixels = stbi_load("../Assets/container.jpg", &width, &height, &ns, 0);
        if (!pixels)
                throw std::runtime_error("加载纹理失败。");

        RHITexture texture0 = RHIGenTexture(RHI_IMAGE_FORMAT_RGB, width, height, pixels);
        stbi_image_free(pixels);

        pixels = stbi_load("../Assets/awesomeface.png", &width, &height, &ns, 0);
        if (!pixels)
                throw std::runtime_error("加载纹理失败。");

        RHITexture texture1 = RHIGenTexture(RHI_IMAGE_FORMAT_RGBA, width, height, pixels);
        stbi_image_free(pixels);

        shader->Bind();
        shader->SetInt("ourSampler2D_0", 0);
        shader->SetInt("ourSampler2D_1", 1);

        bool show_demo_window = false;
        float zNear = 0.01f, zFar = 100.0f, degrees = 45.0f;
        ancivec3 viewXYZ(0.0f, 0.0f, -3.0f);
        float rotateDegrees = -55.0f;
        ancivec3 rotateXZY(1.0f, 0.0f, 0.0f);

        while (!_window->ShouldClose()) {
                _window->PollEvents();

                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                if (show_demo_window)
                        ImGui::ShowDemoWindow(&show_demo_window);

                RHIClearColorBuffer(ancivec4(0.2f));

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

                        ImGui::Text("view");
                        ImGui::SameLine();
                        ImGui::DragFloat3("view", glm::value_ptr(viewXYZ), 0.01f);

                        ImGui::Text("rotateDegrees");
                        ImGui::SameLine();
                        ImGui::DragFloat("rotateDegrees", &rotateDegrees, 1.0f);

                        ImGui::Text("rotateXZY");
                        ImGui::SameLine();
                        ImGui::DragFloat3("rotateXZY", glm::value_ptr(rotateXZY), 0.01f);
                } ImGui::End();

                ancimat4 model{1.0f};
                ancimat4 projection{1.0f};
                ancimat4 view{1.0f};
                model = glm::rotate(model, glm::radians(rotateDegrees), rotateXZY);
                view = glm::translate(view, viewXYZ);
                ancivec2 dimension = _window->GetDimension();
                projection = glm::perspective(glm::radians(degrees), (float) dimension.x / (float) dimension.y, zNear, zFar);

                shader->SetMat4("model", model);
                shader->SetMat4("view", view);
                shader->SetMat4("proj", projection);

                RHIBindTexture(texture0);
                RHIBindTexture(texture1);
                RHIBindVtxBuffer(vtxBuffer);
                RHIDrawIdx(idxBuffer);

                // Rendering
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                ImGuiIO &io = ImGui::GetIO();
                if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                {
                        GLFWwindow* backup_current_context = glfwGetCurrentContext();
                        ImGui::UpdatePlatformWindows();
                        ImGui::RenderPlatformWindowsDefault();
                        glfwMakeContextCurrent(backup_current_context);
                }

                RHISwapBuffers(_window->GetHandle());
        }
}