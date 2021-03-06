/* AUTHOR: 2BKBD, DATE: 2022/1/24 */
#pragma once

#include "APPGUI.h"
#include "Scene/Component/SceneComponentList.h"
#include "Application/MainWindow.h"
#include "Scene/SceneData.h"

struct GUIKitData {
        /* 性能面板 */
        float           deltaTime;
        long            drawTime;
        /* 视图 */
        ArsFramebuffer  framebuffer;
        /* 组件 */
        SceneComponentList *componentList;
        MainWindow*     window;
        /* 场景事件 */
        SceneEventData* p_scene_event;
};

class GUIKit {
public:
        GUIKit();
        void Render(GUIKitData *p_data);

private: /* 主窗口 */
        void DrawPerformance(GUIKitData *p_data);
        void DrawViewport(GUIKitData *p_data);
        void DrawComponents(GUIKitData *p_data);

private: /* 子窗口（编辑组件） */
        void DrawDisableComponentWindow(GameObject *p_data);
             void DrawTransform        (GameObject *p_data);
             void DrawTextures         (GameObject *p_data);
                  void DrawTextureComponent(ArsTexture& texture);

private:
        compid_t        _selected_id = -1;
};