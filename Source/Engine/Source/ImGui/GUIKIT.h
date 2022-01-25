/* AUTHOR: 2BKBD, DATE: 2022/1/24 */
#pragma once

#include "APPGUI.h"
#include "Scene/Component/SceneComponentList.h"
#include "Application/MainWindow.h"

struct GUIKitData {
        /* 性能面板 */
        float           deltaTime;
        long            drawTime;
        /* 视图 */
        RHIFramebuffer  framebuffer;
        /* 组件 */
        SceneComponentList *componentList;
};

struct GUIKitTransformData {
        float*          position;
        float*          rotate;
        float*          scale;
};

class GUIKit {
public:
        float ASPECT;
        void Render(GUIKitData *p_data);

private: /* 主窗口 */
        void DrawPerformance(GUIKitData *p_data);
        void DrawViewport(GUIKitData *p_data);
        void DrawComponents(GUIKitData *p_data);

private: /* 子窗口（编辑组件） */
        void DrawTransformComponent(GUIKitTransformData *p_data);

private:
        compid_t _selected_id = -1;
};