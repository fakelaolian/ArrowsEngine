#include <iostream>
#include "Application/AnciApplication.h"

int main()
{
#ifdef WIN32
        system("chcp 65001");
#endif

        AnciApplication app{"ANCI", 1000, 800};
        app.Run();

        return 0;
}