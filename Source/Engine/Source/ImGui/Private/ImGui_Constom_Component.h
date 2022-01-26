/* AUTHOR: 2BKBD, DATE: 2022/1/25 */
#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace ImGuiInternalCC
{
        using namespace ImGui;

        static inline void PushMultiItemsWidthsAndLabels(const char *labels[], int components, float w_full)
        {
                ImGuiWindow *window = GetCurrentWindow();
                const ImGuiStyle &style = GImGui->Style;
                if (w_full <= 0.0f)
                        w_full = GetContentRegionAvailWidth();

                const float w_item_one =
                        ImMax(1.0f,
                              (w_full - (style.ItemInnerSpacing.x * 2.0f) * (components - 1)) / (float) components) -
                        style.ItemInnerSpacing.x;
                for (int i = 0; i < components; i++)
                        window->DC.ItemWidthStack.push_back(w_item_one - CalcTextSize(labels[i]).x);
                window->DC.ItemWidth = window->DC.ItemWidthStack.back();
        }
}

namespace ImGuiCC
{
        using namespace ImGui;
        inline bool DragFloatExColorN(const std::string tab, const char *labels[], float *v, int components, float v_speed)
        {
                ImGuiWindow *window = GetCurrentWindow();
                if (window->SkipItems)
                        return false;

                ImGuiContext &g = *GImGui;
                bool value_changed = false;
                BeginGroup();

                ImGuiInternalCC::PushMultiItemsWidthsAndLabels(labels, components, 0.0f);
                for (int i = 0; i < components; i++) {
                        PushID(labels[i]);
                        PushID(i);
                        // Particular widget styling
                        ImU32 color;
                        switch (i) {
                                case 0: color = IM_COL32(255,0,0,255); break;
                                case 1: color = IM_COL32(0,255,0,255); break;
                                case 2: color = IM_COL32(0,0,255,255); break;
                        }

                        ImGui::PushStyleColor(ImGuiCol_Text, color);
                        TextUnformatted(labels[i], FindRenderedTextEnd(labels[i]));
                        ImGui::PopStyleColor();
                        SameLine();
                        std::string tab0 = "##" + tab + labels[i];
                        PushItemWidth(GetWindowWidth() * 0.2);
                        ImGui::PushStyleColor(ImGuiCol_Button, color);
                        value_changed |= DragFloat(tab0.c_str(), &v[i], v_speed);
                        ImGui::PopStyleColor();
                        SameLine(0, g.Style.ItemInnerSpacing.x);
                        PopID();
                        PopID();
                        PopItemWidth();
                }

                EndGroup();

                return value_changed;
        }

        inline bool DragFloatExColor3(const std::string tab, float *v, float v_speed)
        {
                const char *labels[] = {"x", "y", "z"};
                return DragFloatExColorN(tab, labels, v, 3, v_speed);
        }

        inline void OffsetText(const char *v)
        {
                float textOffsetPosX = ImGui::GetCursorPosX() + (float) 20;
                ImGui::SetCursorPosX(textOffsetPosX);
                ImGui::Text("%s", v);
        }

        inline void Image(ArsTexture texture, arrovec2 size)
        {
                ImGui::Image((ImTextureID)(intptr_t) ArsGetTextureId(texture), ImVec2(size.x, size.y));
        }

        inline bool ImageButton(ArsTexture texture, arrovec2 size)
        {
                return ImGui::ImageButton(
                        (ImTextureID)(intptr_t) ArsGetTextureId(texture),
                        ImVec2(size.x, size.y)
                );
        }

}