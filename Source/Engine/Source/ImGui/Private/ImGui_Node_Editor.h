/* AUTHOR: 2BKBD, DATE: 2022/2/8 */
#pragma once

#include <blueprint/imnodes.h>

#include <unordered_map>
#include <algorithm>

namespace bp {

        enum _ImPinType {
                NONE,
                NUMBER,
                FLOAT,
                TEXT,
        };

        enum _ImPinKind {
                Input,
                Output
        };

        struct _ImPin {
                int Id;
                std::string Name;
                _ImPinKind Kind;
                _ImPinType Type;
        };

        /**
         * 蓝图节点
         */
        struct _ImNode {
                int Id;
                std::string Name;
                std::vector<_ImPin> Pins; /* size: 2 */
                float value = 0.0f;
        };
        static std::unordered_map<std::string, _ImNode> g_Blueprints;

        /**
         * 连线
         */
        struct Link {
                int Id;
                int InputId;
                int OutputId;
        };

        /* 管理全局蓝图数据 */
        static std::unordered_map<int, _ImNode> g_UsingBlueprints;
        static std::vector<Link>                g_Links;
        static int                              g_CurrentLinkId = 0;

        /* 蓝图组件 */
        static inline void InitAllNodesO() {
                std::vector<_ImPin> pins = {
                        {0, "input", _ImPinKind::Input, _ImPinType::FLOAT},
                         {0, "output", _ImPinKind::Output, _ImPinType::FLOAT}
                };
                _ImNode node {0, "add", pins};

                g_Blueprints.insert({"add", node});
        }

        /* 添加到画布 */
        static inline void PushBlueprint(const std::string& name)
        {
                static int UniqueId = 1;

                _ImNode node = g_Blueprints.at(name);
                node.Id = UniqueId++;
                int i  = 1;
                for (_ImPin& pin : node.Pins) {
                        pin.Id = node.Id + i;
                        ++i;
                }

                g_UsingBlueprints.insert({node.Id, node});
        }

        /* 画蓝图列表 */
        static inline void DrawBlueprints()
        {
                for (std::unordered_map<int, _ImNode>::iterator it=g_UsingBlueprints.begin(); it!=g_UsingBlueprints.end(); ++it) {
                        _ImNode node = it->second;
                        ImNodes::BeginNode(node.Id);

                        ImNodes::BeginNodeTitleBar();
                        ImGui::TextUnformatted(node.Name.c_str());
                        ImNodes::EndNodeTitleBar();

                        for (_ImPin pin : node.Pins) {
                                if (pin.Kind == _ImPinKind::Input) {
                                        ImNodes::BeginInputAttribute(node.Id << 8);
                                        ImGui::TextUnformatted(pin.Name.c_str());
                                        ImNodes::EndInputAttribute();
                                } else {
                                        ImNodes::BeginOutputAttribute(node.Id << 24);
                                        const float text_width = ImGui::CalcTextSize("output").x;
                                        ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
                                        ImGui::TextUnformatted(pin.Name.c_str());
                                        ImNodes::EndOutputAttribute();
                                }
                        }

                        ImNodes::EndNode();
                }

                for (Link link : g_Links)
                        ImNodes::Link(link.Id, link.InputId, link.OutputId);
        }

        static inline void BeginEditor()
        {
                ImGui::Begin("节点编辑器");
                ImNodes::BeginNodeEditor();
        }

        static inline void EndEditor()
        {
                ImNodes::MiniMap();
                ImNodes::EndNodeEditor();

                Link link;
                if (ImNodes::IsLinkCreated(&link.InputId, &link.OutputId)) {
                        link.Id = ++g_CurrentLinkId;
                        g_Links.push_back(link);

                }

                int linkId;
                if (ImNodes::IsLinkDestroyed(&linkId)) {
                        auto iter =
                                std::find_if(g_Links.begin(), g_Links.end(), [linkId](const Link& link){
                                        return linkId == link.Id;
                                });
                        assert(iter != g_Links.end());
                        g_Links.erase(iter);
                }

                ImGui::End();
        }

}
