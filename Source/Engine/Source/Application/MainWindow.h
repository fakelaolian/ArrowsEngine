/* AUTHOR: 2BKBD, DATE: 2022/1/21 */
#pragma once

#include <arrows_core.h>
#include <RHI.h>

class MainWindow {
public:
        MainWindow(const char *title, int w, int h);
        ~MainWindow();

        enum CursorDirection { F, B, R, L };

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

        inline float GetLastMouseX()
        { return _last_mouse_x; }

        inline float GetLastMouseY()
        { return _last_mouse_y; }

        inline uint32_t GetWidth()
        { return _width; }

        inline uint32_t GetHeight()
        { return _height; }

        /* 隐藏鼠标 */
        inline void DisableCursor()
        {
                if (_disable_mouse)
                        return;

                _disable_mouse = true;
                RHISetCursorMode(_window_handle, RHI_CURSOR_DISABLE);
        }

        /* 显示鼠标 */
        inline void NormalCursor()
        {
                if (!_disable_mouse)
                        return;

                _disable_mouse = false;
                RHISetCursorMode(_window_handle, RHI_CURSOR_NORMAL);
        }

        /* 判断当前鼠标左右横轴移动方向 */
        inline CursorDirection GetCursorDirectionX()
        { return (_last_mouse_x > _mouse_x) ? R : L; }

        /* 判断当前鼠标纵轴移动方向 */
        inline CursorDirection GetCursorDirectionY()
        { return (_last_mouse_y > _mouse_y) ? F : B; }

private:
        inline void SetDimension(uint32_t w, uint32_t h)
        {
                _width = w;
                _height = h;
                _aspect = (float) _width / _height;
        }

        inline void SetMouseXY(float x, float y)
        {
                _last_mouse_x = _mouse_x;
                _last_mouse_y = _mouse_y;
                _mouse_x      = x;
                _mouse_y      = y;
        }

private:
        uint32_t  _width;
        uint32_t  _height;
        float     _mouse_x;
        float     _mouse_y;
        float     _last_mouse_x;
        float     _last_mouse_y;
        float     _aspect;
        bool      _disable_mouse = false;
        RHIWindow _window_handle;

};