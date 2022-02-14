#include <iostream>
#include "Application/MainApplication.h"

int main()
{
#ifdef WIN32
        system("chcp 65001");
#endif

        MainApplication app{"ARROWS", 1680, 1280};
        app.Run();

        return 0;
}