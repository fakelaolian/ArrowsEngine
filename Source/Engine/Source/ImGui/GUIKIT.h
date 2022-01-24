/* AUTHOR: 2BKBD, DATE: 2022/1/24 */
#pragma once

#include "APPGUI.h"

struct GUIKitData {
        /* 性能面板 */
        float           deltaTime;
        long            drawTime;
        /* 视图 */
        RHIFramebuffer  framebuffer;
};

class GUIKit {
public:
        static float ASPECT;
        static void Render(GUIKitData *p_data);
};