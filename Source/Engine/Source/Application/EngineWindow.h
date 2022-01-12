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

        inline const RHIDimension &GetDimension() const
        { return _dimension; }

        static inline void PollEvents()
        { RHIPollEvents(); };

private:
        RHIDimension            _dimension;
        RHIWindow               _window;

};
