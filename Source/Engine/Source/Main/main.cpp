#include "Application/EngineApplication.h"

int main()
{
#ifdef WIN32
        system("chcp 65001");
#endif

        EngineApplication application {};
        application.StartEngine();

        return 0;
}