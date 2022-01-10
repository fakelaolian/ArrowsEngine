#include "Application/EngineApplication.h"
#include <RHI/RHI.h>
int main()
{
#ifdef WIN32
        system("chcp 65001");
#endif

        EngineApplication application {AnciEnumGraphicsApi::OpenGL};
        application.StartEngine();

        return 0;
}