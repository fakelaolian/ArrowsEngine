/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#include <AnciCore.h>
#include <AnciWindow.h>

/**
 * 引擎应用程序，负责启动引擎
 */
class EngineApplication {
public:
        explicit                EngineApplication(AnciEnumGraphicsApi api);
        void                    StartEngine();

private:
        anciptr<AnciWindow>     _window;
};