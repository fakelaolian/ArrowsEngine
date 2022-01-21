/* AUTHOR: 2BKBD, DATE: 2022/1/19 */
#pragma once

#include <RHI.h>
#include <anci_core.h>

class AnciApplication {
public:
        AnciApplication(uint32_t w, uint32_t h, const char *title);
        ~AnciApplication() = default;

        inline void SetDimension(uint32_t w, uint32_t h)
        {
                _width = w;
                _height = h;
                _aspect = (float) _width / _height;
        }

        void Run();

private:
        RHIWindow _window;
        uint32_t  _width;
        uint32_t  _height;
        float     _aspect;

};