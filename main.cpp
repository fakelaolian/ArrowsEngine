#include "Application/EngineApplication.h"

int main()
{
        EngineApplication application {AnciEnumGraphicsApi::OpenGL};
        application.StartEngine();

        return 0;
}