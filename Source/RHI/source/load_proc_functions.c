/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
#include "RHI.h"

#include <stdio.h>

/* 不同API的实现，规范是RHIGraphAPIBits枚举的名称加上RHIImpl
 *
 * 示例：
 *   VulkanRHIImpl. OpenGLRHIImpl
 * */
extern void OpenGLRHIImpl();

/** 加载RHI实现函数 */
int RHIProcAddressInit(RHIGraphAPIBits graphApiBit)
{
        switch (graphApiBit) {
                case OpenGL:  OpenGLRHIImpl(); break;
                case Vulkan:
                case DX12:
                default: printf("不支持的API"); return RHI_FALSE;
        }

        return RHI_TRUE;
}