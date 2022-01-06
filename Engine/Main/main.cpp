#include "Application/EngineApplication.h"
#include <RHI/RHI.h>
int main()
{
        EngineApplication application {AnciEnumGraphicsApi::OpenGL};
        application.StartEngine();

        return 0;
}