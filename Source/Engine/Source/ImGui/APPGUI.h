/* AUTHOR: 2BKBD, DATE: 2022/1/23 */
#pragma once

#include <RHI.h>

class APPGUI {
public:
        APPGUI(RHIWindow h);
        ~APPGUI();

        void BeginRender();
        void EndRender();

private:
};
