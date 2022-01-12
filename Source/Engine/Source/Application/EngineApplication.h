/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#include <AnciCore.h>
#include "EngineWindow.h"

/**
 * 引擎应用程序，负责启动引擎
 */
class EngineApplication {
public:
        explicit                EngineApplication();
        void                    StartEngine();

private:
        anciptr<EngineWindow>   _window;
};