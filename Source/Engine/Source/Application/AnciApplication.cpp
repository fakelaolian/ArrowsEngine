/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "AnciApplication.h"

#include "Render/GameObject.h"

AnciApplication::AnciApplication(uint32_t w, uint32_t h, const char *title)
{
        RHIProcAddressInit(OpenGL);

        /* 创建窗口 */
        RHICreateWindow(title, w, h, &_window);

        if (!_window)
                throw std::runtime_error("创建窗口失败。");
}

void AnciApplication::Run()
{
        std::vector<mloader::mesh_t> meshs = mloader::load_model("C:/Users/procf/Desktop/untitled.obj");
        GameObject object{meshs};

        RHIShader cubeShader = RHICreateShader("../../../Source/Engine/Shaders/cube.alsl");

        while(!RHIWindowShouldClose(_window)) {
                RHIPollEvents();
                RHIClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);

                RHIBindShader(cubeShader);
                /* 游戏主循环 */
                object.Draw();

                RHISwapBuffers(_window);
        }

        RHIDestroyWindow(_window);
        RHITerminate();
}