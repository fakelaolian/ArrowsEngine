/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <RHI.h>
#include <anci_core.h>
#include "AnciWindow.h"

class AnciApplication {
public:
        AnciApplication(const char *title, uint32_t w, uint32_t h);
        ~AnciApplication() = default;

        void Run();

private:
        anciptr<AnciWindow> _window;

};