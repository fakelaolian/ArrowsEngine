/* AUTHOR: 2BKBD, DATE: 2022/2/8 */
#pragma once

#include <blueprint/imnodes.h>
#include <map>
#include <unordered_map>
#include <algorithm>

namespace bp {

    enum _ImPinType {
        NONE,
        NUMBER,
        FLOAT,
        FLOAT3,
        TEXT,
    };

    enum _ImPinKind {
        Input,
        Output
    };

    struct _ImNode;

    struct _ImPin {
        int Id;
        std::string Name;
        _ImPinKind Kind;
        _ImPinType Type;
        std::string CompId;
        int Iv;
        float Fv;
        float F3v[3];
        char Text[512];
        _ImNode *Node;
        std::map<int, const _ImPin *> Links;
        bool HasValue;
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

    /**
     * 连线
     */
    struct Link {
        int Id;
        int InputId;
        int OutputId;
    };

    /**
     * 上下文管理
     */
    struct _ImNodesContextIO {
        int CurrentLinkId = 0;                                  /* 自增长ID */
        std::unordered_map<int, _ImNode> InCanvasBlueprints;    /* 所有在画布的蓝图 */
        std::unordered_map<int, _ImPin *> InBlueprintPin;       /* 所有在画布的引脚 */
        std::vector<Link> Links;                                /* 链接数据 */
        std::unordered_map<std::string, _ImNode> Blueprints;    /* 蓝图组件列表 */

        /* 检查Input引脚是否被链接 */
        const _ImPin *CheckInputLinkTo(int inputId)
        {
            auto iter =
                std::find_if(Links.begin(), Links.end(), [inputId](const Link &link) {
                    return link.InputId == inputId;
                });
            return iter != Links.end() ? InBlueprintPin[iter->OutputId] : nullptr;
        }

    };

    /* 管理全局蓝图数据 */
    static _ImNodesContextIO g_ContextIO;


    /* 蓝图组件 */
    static inline void InitAllNodesO()
    {
        std::vector<_ImPin> pins = {
            {0, "input",  _ImPinKind::Input,  _ImPinType::FLOAT},
            {0, "output", _ImPinKind::Output, _ImPinType::FLOAT}
        };
        _ImNode node{0, "add", pins};

        std::vector<_ImPin> imagePins = {
            {0, "基础色",  _ImPinKind::Input,  _ImPinType::FLOAT3},
            {0, "次表面", _ImPinKind::Input, _ImPinType::FLOAT},
            {0, "金属感", _ImPinKind::Input, _ImPinType::FLOAT},
            {0, "高光染色", _ImPinKind::Input, _ImPinType::FLOAT},
        };
        _ImNode image{0, "image", imagePins};

        g_ContextIO.Blueprints.insert({"add", node});
        g_ContextIO.Blueprints.insert({"image", image});
    }

    /**
     * 添加到画布
     */
    static inline void PushBlueprint(const std::string &name)
    {
        static int UniqueId = 1;

        _ImNode node = g_ContextIO.Blueprints.at(name);
        node.Id = UniqueId++;
        /* 生成蓝图Id和组件Id */
        for (_ImPin &pin: node.Pins) {
            pin.Id = node.Id + UniqueId++;
            pin.CompId = ("##" + pin.Name + std::to_string(pin.Id));
            UniqueId++;
        }

        auto iter = g_ContextIO.InCanvasBlueprints.insert({node.Id, node});
        _ImNode *p_node = &iter.first->second;
        for (_ImPin &pin: p_node->Pins) {
            pin.Node = p_node; // 在_ImPin对象中存储它的节点指针
            g_ContextIO.InBlueprintPin.insert({pin.Id, &pin});
        }
    }

    /**
     * 画蓝图列表
     */
    static inline void DrawBlueprints()
    {
        for (std::unordered_map<int, _ImNode>::iterator it = g_ContextIO.InCanvasBlueprints.begin();
             it != g_ContextIO.InCanvasBlueprints.end(); ++it) {
            _ImNode &node = it->second;
            ImNodes::BeginNode(node.Id);

            ImNodes::BeginNodeTitleBar();
            ImGui::TextUnformatted(node.Name.c_str());
            ImNodes::EndNodeTitleBar();

            /* 绘制引脚组件 */
            for (_ImPin &pin: node.Pins) {
                if (pin.Kind == _ImPinKind::Input) {
                    ImNodes::BeginInputAttribute(pin.Id);
                    ImGui::TextUnformatted(pin.Name.c_str());
                    ImGui::SameLine();

                    // 检查引脚是否被链接
                    const _ImPin *link_pin = g_ContextIO.CheckInputLinkTo(pin.Id);
                    if (link_pin != nullptr) {
                        pin.HasValue = true;
                        pin.Links[link_pin->Id] = link_pin;
                    }

                    ImGui::PushItemWidth(140.0f);
                    if (!pin.HasValue) {
                        switch (pin.Type) {
                            case NONE:
                                break;
                            case NUMBER:
                                ImGui::DragInt(pin.CompId.c_str(), &pin.Iv);
                                ImGui::PopItemWidth();
                                break;
                            case FLOAT:
                                ImGui::DragFloat(pin.CompId.c_str(), &pin.Fv);
                                break;
                            case FLOAT3:
                                ImGui::DragFloat3(pin.CompId.c_str(), pin.F3v, 0.01f);
                                break;
                            case TEXT:
                                ImGui::InputText(pin.CompId.c_str(), pin.Text,
                                                 sizeof(pin.Text));
                                break;
                        }
                    }
                    ImGui::PopItemWidth();

                    ImNodes::EndInputAttribute();
                } else {
                    ImNodes::BeginOutputAttribute(pin.Id);
                    const float text_width = ImGui::CalcTextSize(pin.Name.c_str()).x;
                    ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
                    ImGui::TextUnformatted(pin.Name.c_str());
                    ImNodes::EndOutputAttribute();
                }
            }

            ImNodes::EndNode();
        }

        for (Link link: g_ContextIO.Links)
            ImNodes::Link(link.Id, link.InputId, link.OutputId);
    }

    /**
     * 开始编辑器渲染
     */
    static inline void BeginEditor()
    {
        ImGui::Begin("节点编辑器");
        ImNodes::BeginNodeEditor();
    }

    /**
     * 结束编辑器渲染
     */
    static inline void EndEditor()
    {
        ImNodes::MiniMap();
        ImNodes::EndNodeEditor();

        Link link;
        if (ImNodes::IsLinkCreated(&link.OutputId, &link.InputId)) {
            link.Id = ++g_ContextIO.CurrentLinkId;
            g_ContextIO.Links.push_back(link);
        }

        int linkId;
        if (ImNodes::IsLinkDestroyed(&linkId)) {
            auto iter =
                std::find_if(g_ContextIO.Links.begin(), g_ContextIO.Links.end(),
                             [linkId](const Link &link) {
                                 return linkId == link.Id;
                             });
            assert(iter != g_ContextIO.Links.end());

            /* 删除链接以及状态 */
            _ImPin *p_pin = g_ContextIO.InBlueprintPin[iter->InputId];
            p_pin->Links.erase(iter->OutputId);
            p_pin->HasValue = false;
            g_ContextIO.Links.erase(iter);
        }

        ImGui::End();
    }

}
