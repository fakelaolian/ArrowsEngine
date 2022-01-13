/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#include <RHI.h>

class EngineWindow {
public:
        EngineWindow(const char *title, int w, int h);

        ~EngineWindow()
        {
                RHIDeleteWindow(_window);
                RHITerminate();
        }

        inline RHIWindow GetHandle()
        { return _window; };

        inline bool ShouldClose()
        { return RHIWindowShouldClose(_window); };

        inline void SetDimension(int x, int y)
        { _dimension = {x, y}; }

        inline void SetCursor(float x, float y)
        { _cursor = {x, y}; }

        inline const RHIDimension2f &GetCursor()
        { return _cursor; }

        inline const RHIDimension2i &GetDimension() const
        { return _dimension; }

        static inline void PollEvents()
        { RHIPollEvents(); };

private:
        RHIDimension2f          _cursor;
        RHIDimension2i          _dimension;
        RHIWindow               _window;

};
