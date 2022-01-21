/* AUTHOR: 2BKBD, DATE: 2022/1/21 */
#pragma once

#include <anci_core.h>
#include <RHI.h>

class AnciWindow {
public:
        AnciWindow(const char *title, int w, int h);
        ~AnciWindow();

        inline bool ShouldClose()
        { return RHIWindowShouldClose(_window_handle); }

        inline RHIWindow GetHandle()
        { return _window_handle; }

        inline float GetAspect()
        { return _aspect; }

        inline float GetMouseX()
        { return _mouse_x; }

        inline float GetMouseY()
        { return _mouse_y; }

private:
        inline void SetDimension(uint32_t w, uint32_t h)
        {
                _width = w;
                _height = h;
                _aspect = (float) _width / _height;
        }

        inline void SetMouseXY(float x, float y)
        {
                _mouse_x = x;
                _mouse_y = y;
        }

private:
        uint32_t  _width;
        uint32_t  _height;
        float     _mouse_x;
        float     _mouse_y;
        float     _aspect;
        RHIWindow _window_handle;

};