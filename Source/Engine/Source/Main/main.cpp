#include <iostream>
#include "Application/AnciApplication.h"

int main()
{
#ifdef WIN32
        system("chcp 65001");
#endif

        AnciApplication app{1000, 800, "ANCI"};
        app.Run();

        return 0;
}