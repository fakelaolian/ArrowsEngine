/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <RHI.h>
#include <anci_core.h>

class anci_application {
public:
        anci_application(uint32_t w, uint32_t h, const char *title);
        ~anci_application() = default;

        void Run();

private:
        RHIWindow _window;

};