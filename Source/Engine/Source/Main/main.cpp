#include <iostream>
#include "Application/anci_application.h"

int main()
{
#ifdef WIN32
        system("chcp 65001");
#endif

        anci_application app{600, 800, "ANCI"};
        app.Run();

        return 0;
}