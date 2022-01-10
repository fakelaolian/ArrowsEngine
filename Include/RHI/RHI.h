/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#include <AnciCore.h>

#ifndef RHIVtxBuffer
  typedef void * RHIVtxBuffer;
#endif

#ifndef RHIIdxBuffer
  typedef void * RHIIdxBuffer;
#endif

/**
 * RHI函数指针，命名规范：
 *      1. typedef <Result> <ANCI_RHI_*>();
 *      2. 定义导出函数: ANCIAPI <ANCI_RHI_*> <变量名去掉函数指针命名的下划线>
 *      3. 定义宏，使用函数
 *
 * 示例：
 *      typedef void (*ANCI_RHI_TEST)();
 *      ANCIAPI ANCI_RHI_TEST ANCIRHITEST;
 *      #define RHITest ANCIRHITEST
 */
typedef void (*ANCI_RHI_VIEWPORT)(u32 x, u32 y, u32 w, u32 h);
ANCIAPI ANCI_RHI_VIEWPORT ANCIRHIVIEWPORT;
#define RHIViewport ANCIRHIVIEWPORT
typedef void (*ANCI_RHI_SWAP_BUFFERS)(ANCI_WINDOW_HANDLE h);
ANCIAPI ANCI_RHI_SWAP_BUFFERS ANCIRHISWAPBUFFERS;
#define RHISwapBuffers ANCIRHISWAPBUFFERS
typedef void (*ANCI_RHI_GEN_VTXBUFFER)(ancivec2);
ANCIAPI ANCI_RHI_GEN_VTXBUFFER ANCIRHIGENVTXBUFFER;
#define RHIGenVtxBuffer ANCIRHIGENVTXBUFFER
typedef void (*ANCI_RHI_GEN_IDXBUFFER)();
ANCIAPI ANCI_RHI_GEN_IDXBUFFER ANCIRHIGENIDXBUFFER;
#define RHIGenIdxBuffer ANCIRHIGENIDXBUFFER

/**
 * 加载对应的API函数
 */
ANCIAPI void RHIApiLoad();