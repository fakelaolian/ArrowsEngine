/* AUTHOR: 2BKBD, DATE: 2022/1/24 */
#include "GUIKIT.h"

#include "Private/ImGui_Constom_Component.h"
#include "Loader/TextureLoader.h"

GUIKit::GUIKit()
{
//        int w, h, channel;
//        arsuc *pixels = _stbi_load("../../../UI/lock&unlock/lock.png", &w, &h, &channel);
//
//        ArsTexture2DCreateInfo createInfo = {};
//        createInfo.width = w;
//        createInfo.height = h;
//        createInfo.pPixels = pixels;
//        createInfo.format = ARS_IMAGE_FORMAT_SRGB;
//
//        ArsCreateTexture2D(&createInfo, &_ui_lock);
}

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
                ArsTexture ftex = ArsGetFramebufferTexture(p_data->framebuffer);
                ImTextureID viewportId = (ImTextureID)(intptr_t)ArsGetTextureId(ftex);
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
        ImGui::Begin("对象列表");
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
                        DrawDisableComponentWindow(gameComponent.GetInstance());
                }
        }
        ImGui::End();
}

void GUIKit::DrawDisableComponentWindow(GameObject *p_data)
{
        if (ImGui::Begin("组件")) {
                if (ImGui::CollapsingHeader("变换")) {
                        float dragOffsetPosX = ImGui::GetCursorPosX() + (float) 40;
                        ImGuiCC::OffsetText("位置");
                        ImGui::SetCursorPosX(dragOffsetPosX);
                        ImGuiCC::DragFloatExColor3("position", glm::value_ptr(p_data->transform3D.position), 0.01f);
                        ImGuiCC::OffsetText("旋转");
                        ImGui::SetCursorPosX(dragOffsetPosX);
                        ImGuiCC::DragFloatExColor3("rotation", glm::value_ptr(p_data->transform3D.rotation), 0.01f);
                        ImGuiCC::OffsetText("缩放");
                        ImGui::SetCursorPosX(dragOffsetPosX);
                        ImGuiCC::DragFloatExColor3("scale", glm::value_ptr(p_data->transform3D.scale), 0.01f);
                }

//                if (ImGui::CollapsingHeader("纹理")) {
//                        if (ImGuiCC::ImageButton(p_data->GetTexture(), arosvec2(80,80)))
//                                ImGui::OpenPopup("arrows_textures_popups");
//
//                        if (ImGui::BeginPopup("arrows_textures_popups")) {
//                                ImGui::Text("Nothing");
//                                ImGui::EndPopup();
//                        }
//                }
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