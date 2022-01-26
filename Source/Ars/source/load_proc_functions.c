/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
#include "Ars.h"

#include <stdio.h>

/* 不同API的实现，规范是ArsGraphAPIBits枚举的名称加上ArsImpl
 *
 * 示例：
 *   VulkanArsImpl. OpenGLArsImpl
 * */
extern void OpenGLArsImpl();

/** 加载Ars实现函数 */
int ArsProcAddressInit(ArsGraphAPIBits graphApiBit)
{
        switch (graphApiBit) {
                case OpenGL:  OpenGLArsImpl(); break;
                case Vulkan:
                case DX12:
                default: printf("不支持的API"); return ARS_FALSE;
        }

        return ARS_TRUE;
}