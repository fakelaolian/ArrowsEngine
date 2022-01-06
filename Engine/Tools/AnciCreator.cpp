/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include <ATools/AnciCreator.h>

#include "Platform/OpenGL/OpenGLWindow.h"

extern AnciEnumGraphicsApi g_AnciGraphicsApi;

anciptr<AnciWindow> AnciCreateWindow(const String& title, ancivec2 dimension)
{
        switch (g_AnciGraphicsApi) {
                case OpenGL: return std::make_unique<OpenGLWindow>(title, dimension);
                default: throw std::runtime_error("不支持的图形API");
        }
}

