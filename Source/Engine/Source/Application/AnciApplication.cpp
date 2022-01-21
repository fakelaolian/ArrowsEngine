/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "AnciApplication.h"

#include "Scene/GameObject.h"
#include "Scene/SceneCamera.h"

AnciApplication::AnciApplication(uint32_t w, uint32_t h, const char *title)
{
        RHIProcAddressInit(OpenGL);

        /* 创建窗口 */
        RHICreateWindow(title, w, h, &_window);
        RHISetUserPointer(_window, this);

        _aspect = (float) w / h;

        /* 设置窗口回调函数 */
        RHISetWindowResizeCallback(_window, [](RHIWindow window, int w, int h) {
                RHIViewport(0, 0, w, h);
                AnciApplication *app = (AnciApplication *) RHIGetUserPointer(window);
                app->SetDimension(w, h);
        });

        if (!_window)
                throw std::runtime_error("创建窗口失败。");
}

void AnciApplication::Run()
{
        std::vector<mloader::mesh_t> meshs = mloader::load_model("C:/Users/procf/Desktop/untitled.obj");
        meshs[0].texture = "D:\\projects\\AnciEngine\\Assets\\container2.png";

        GameObject object{meshs[0]};

        RHIShader cubeShader = RHICreateShader(GET_SHADER(normalize.alsl));

        SceneCamera sceneCamera{ancivec3(0.0f, 0.0f, 3.0f)};

        /* 游戏主循环 */
        RHIEnable(RHI_DEPTH_TEST, RHI_TRUE);
        while(!RHIWindowShouldClose(_window)) {
                RHIPollEvents();
                RHIClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);

                sceneCamera.Update(_aspect);

                RHIBindShader(cubeShader);
                RHIUniformMatrix4fv(cubeShader, "proj", glm::value_ptr(sceneCamera.GetProjectionMatrix()));
                RHIUniformMatrix4fv(cubeShader, "view", glm::value_ptr(sceneCamera.GetViewMatrix()));
                RHIUniformMatrix4fv(cubeShader, "model", glm::value_ptr(object.GetModelMatrix()));

                object.Draw();

                RHISwapBuffers(_window);
        }

        RHIDestroyWindow(_window);
        RHITerminate();
}