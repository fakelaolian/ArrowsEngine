/* AUTHOR: 2BKBD, DATE: 2022/1/25 */
#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace ImGuiInternalCC
{
        using namespace ImGui;

        static void PushMultiItemsWidthsAndLabels(const char *labels[], int components, float w_full)
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
        bool DragFloatNEx(const std::string tab, const char *labels[], float *v, int components, float v_speed)
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
                        TextUnformatted(labels[i], FindRenderedTextEnd(labels[i]));
                        // Particular widget styling
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0,255,0,255));
                        ImGui::PopStyleColor();
                        SameLine();
                        std::string tab0 = "##" + tab + labels[i];
                        PushItemWidth(GetWindowWidth() * 0.2);
                        value_changed |= DragFloat(tab0.c_str(), &v[i], v_speed);
                        SameLine(0, g.Style.ItemInnerSpacing.x);
                        PopID();
                        PopID();
                        PopItemWidth();
                }

                EndGroup();

                return value_changed;
        }

}