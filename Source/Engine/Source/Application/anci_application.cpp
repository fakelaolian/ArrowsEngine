/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#include "anci_application.h"

anci_application::anci_application(uint32_t w, uint32_t h, const char *title)
{
        RHIProcAddressInit(OpenGL);

        /* 创建窗口 */
        RHICreateWindow(title, w, h, &_window);

        if (!_window)
                throw std::runtime_error("创建窗口失败。");
}

void anci_application::Run()
{
        while(!RHIWindowShouldClose(_window)) {
                RHIPollEvents();
                RHIClearColorBuffer(0.2f, 0.2f, 0.2f, 0.2f);

                /* 游戏主循环 */

                RHISwapBuffers(_window);
        }

        RHIDestroyWindow(_window);
        RHITerminate();
}