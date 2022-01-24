#include <iostream>
#include "Application/MainApplication.h"

int main()
{
#ifdef WIN32
        system("chcp 65001");
#endif

        MainApplication app{"ARROWS", 1000, 800};
        app.Run();

        return 0;
}