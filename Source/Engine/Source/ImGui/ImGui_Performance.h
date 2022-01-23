/* AUTHOR: 2BKBD, DATE: 2022/1/23 */
#pragma once
/* DESCRIPTOR: 性能面板 */

#include <imgui/imgui.h>

struct COMP_ImGUI_Performance_Data {
        float DeltaTime;
        long  DrawTime;
};

/* 渲染性能面板 */
static inline void COMP_ImGUI_Performance_Draw(COMP_ImGUI_Performance_Data *p_data)
{
        if (ImGui::Begin("Performance")) {
                ImGui::Text("delta time: %f", p_data->DeltaTime);
                ImGui::Text("draw time: %ldms", p_data->DrawTime);
        } ImGui::End();
}