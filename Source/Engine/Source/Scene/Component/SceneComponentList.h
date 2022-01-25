/* AUTHOR: 2BKBD, DATE: 2022/1/24 */
#pragma once

#include "SkyBox.h"
#include "GameObject.h"

// std
#include <unordered_map>

/* 场景中的组件列表 */
class SceneComponentList {
public:
        SceneComponentList() {};
        ~SceneComponentList() = default;

        inline void PutGameComponent(GameComponent<GameObject>& comp)
        { _components.emplace(comp.GetId(), comp); }

        inline std::unordered_map<compid_t, GameComponent<GameObject>&>& GetGameComponents()
        { return _components; }

private:
        std::unordered_map<compid_t, GameComponent<GameObject>&> _components;
};