/* AUTHOR: 2BKBD, DATE: 2022/1/24 */
#include "GUIKIT.h"

#include <imgui/imgui.h>

void GUIKit::DrawPerformance(GUIKitData *p_data)
{
        if (ImGui::Begin("性能面板")) {
                ImGui::Text("delta time: %f", p_data->deltaTime);
                ImGui::Text("draw time: %ldms", p_data->drawTime);
        } ImGui::End();
}

void GUIKit::DrawViewport(GUIKitData *p_data)
{
        ImGui::Begin("场景视图");
        {
                RHITexture ftex = RHIGetFramebufferTexture(p_data->framebuffer);
                ImTextureID viewportId = (ImTextureID)(intptr_t)RHIGetTextureId(ftex);
                ImGui::BeginChild("ViewportRender");
                ImVec2 wsize = ImGui::GetWindowSize();
                ImGui::Image((ImTextureID)viewportId, wsize, ImVec2(0, 1), ImVec2(1, 0));
                ImGui::EndChild();
                GUIKit::ASPECT = wsize.x / wsize.y;
        }
        ImGui::End();
}

void GUIKit::DrawComponents(GUIKitData *p_data)
{
        ImGui::Begin("组件列表");
        {
                auto *complist = p_data->componentList;
                auto &comps    = complist->GetGameComponents();

                ImGuiTreeNodeFlags __ImGuiTreeNodeBaseFlags = ImGuiTreeNodeFlags_SpanAvailWidth;

                /* 场景中的游戏对象组件列表 */
                for (auto iter = comps.begin(); iter != comps.end(); ++iter) {
                        auto    comp   = iter->second;
                        compid_t _compid = comp.GetId();

                        ImGuiTreeNodeFlags _ImGuiTreeNodeFlags = __ImGuiTreeNodeBaseFlags;

                        if (_selected_id == _compid)
                                _ImGuiTreeNodeFlags |= ImGuiTreeNodeFlags_Selected;

                        /* 判断条目有没有被选中 */
                        bool is_open = ImGui::TreeNodeEx(comp.GetName(), _ImGuiTreeNodeFlags);
                        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                                _selected_id = _compid;

                        if (is_open)
                                ImGui::TreePop();
                }

                if (_selected_id != -1) {
                        auto gameComponent = comps.at(_selected_id);
                        GameObject *gameObject = gameComponent.GetInstance();
                        GUIKitTransformData data{
                                glm::value_ptr(gameObject->GetPosition()),
                                glm::value_ptr(gameObject->GetRotation()),
                                glm::value_ptr(gameObject->GetScale()),
                        };
                        DrawTransformComponent(&data);
                }
        }
        ImGui::End();
}

void GUIKit::DrawTransformComponent(GUIKitTransformData *p_data)
{
        if (ImGui::Begin("变换")) {
                ImGui::DragFloat3("位置", p_data->position, 0.01f);
                ImGui::DragFloat3("旋转", p_data->rotate, 0.01f);
                ImGui::DragFloat3("缩放", p_data->scale, 0.01f);
        } ImGui::End();
}

void GUIKit::Render(GUIKitData *p_data)
{
        bool showDemo = true;
        ImGui::ShowDemoWindow(&showDemo);

        DrawPerformance(p_data);
        DrawViewport(p_data);
        DrawComponents(p_data);
}