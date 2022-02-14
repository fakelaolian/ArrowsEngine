/* AUTHOR: 2BKBD, DATE: 2022/2/14 */
#pragma once

// 场景事件数据结构体
struct SceneEventData {
    /* 判断对应的键是否按下 */
    bool   MoveKey_W;
    bool   MoveKey_A;
    bool   MoveKey_S;
    bool   MoveKey_D;
    bool   MoveKey_SPACE;
    bool   MoveKey_LEFT_CTRL;
    bool   MouseButton2Press;         /* 鼠标右键是否按下 */

    float  DetailTime;                /* 每帧时间 */
    float  Aspect;                    /* 窗口的纵横比 */

    void ResetKeys()
    {
        MoveKey_W = false;
        MoveKey_A = false;
        MoveKey_S = false;
        MoveKey_D = false;
        MoveKey_SPACE = false;
        MoveKey_LEFT_CTRL = false;
        MouseButton2Press = false;
    }
};