/* AUTHOR: 2BKBD, DATE: 2022/1/24 */
#include "GUIKIT.h"

#include <imgui/imgui.h>

float GUIKit::ASPECT = 1.0f;

void GUIKit::Render(GUIKitData *p_data)
{
        bool showDemo = true;
        ImGui::ShowDemoWindow(&showDemo);

        if (ImGui::Begin("Performance")) {
                ImGui::Text("delta time: %f", p_data->deltaTime);
                ImGui::Text("draw time: %ldms", p_data->drawTime);
        } ImGui::End();

        ImGui::Begin("Viewport");
        {
                RHITexture ftex = RHIGetFramebufferTexture(p_data->framebuffer);
                ImTextureID viewportId = (ImTextureID)(intptr_t)RHIGetTextureId(ftex);
                ImGui::BeginChild("ViewportRender");
                ImVec2 wsize = ImGui::GetWindowSize();
                ImGui::Image((ImTextureID)viewportId, wsize, ImVec2(0, 1), ImVec2(1, 0));
                ImGui::EndChild();
                ASPECT = wsize.x / wsize.y;
        }
        ImGui::End();
}