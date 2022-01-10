/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#include <AnciCore.h>

#ifndef RHIVtxBuffer
  typedef void * RHIVtxBuffer;
#endif

#ifndef RHIIdxBuffer
  typedef void * RHIIdxBuffer;
#endif

#ifndef RHIShader
  typedef void * RHIShader;
#endif

enum RHIEnumCreateShaderMode {
        RHI_VERTEX_SHADER,
        RHI_FRAGMENT_SHADER,
};

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
typedef void (*ANCI_RHI_VIEWPORT)(anciu32 x, anciu32 y, anciu32 w, anciu32 h);
ANCIAPI ANCI_RHI_VIEWPORT ANCIRHIVIEWPORT;
#define RHIViewport ANCIRHIVIEWPORT
typedef void (*ANCI_RHI_SWAP_BUFFERS)(ANCI_WINDOW_HANDLE h);
ANCIAPI ANCI_RHI_SWAP_BUFFERS ANCIRHISWAPBUFFERS;
#define RHISwapBuffers ANCIRHISWAPBUFFERS
typedef RHIVtxBuffer (*ANCI_RHI_GEN_VTXBUFFER)(float *vertices, anciu32 count);
ANCIAPI ANCI_RHI_GEN_VTXBUFFER ANCIRHIGENVTXBUFFER;
#define RHIGenVtxBuffer ANCIRHIGENVTXBUFFER
typedef RHIIdxBuffer (*ANCI_RHI_GEN_IDXBUFFER)(anciu32 *indices, anciu32 count);
ANCIAPI ANCI_RHI_GEN_IDXBUFFER ANCIRHIGENIDXBUFFER;
#define RHIGenIdxBuffer ANCIRHIGENIDXBUFFER
typedef void (*ANCI_RHI_DESTROY_VTX_BUFFER)(RHIVtxBuffer);
ANCIAPI ANCI_RHI_DESTROY_VTX_BUFFER ANCIRHIDESTROYVTXBUFFER;
#define RHIDestroyVtxBuffer ANCIRHIDESTROYVTXBUFFER
typedef void (*ANCI_RHI_DESTROY_IDX_BUFFER)(RHIIdxBuffer);
ANCIAPI ANCI_RHI_DESTROY_IDX_BUFFER ANCIRHIDESTROYIDXBUFFER;
#define RHIDestroyIdxBuffer ANCIRHIDESTROYIDXBUFFER
typedef void (*ANCI_RHI_BIND_VTX)(RHIVtxBuffer);
ANCIAPI ANCI_RHI_BIND_VTX ANCIRHIBINDVTX;
#define RHIBindVtxBuffer ANCIRHIBINDVTX
typedef void (*ANCI_RHI_DRAW_VTX)(RHIVtxBuffer);
ANCIAPI ANCI_RHI_DRAW_VTX ANCIRHIDRAWVTX;
#define RHIDrawVtx ANCIRHIDRAWVTX
typedef void (*ANCI_RHI_DRAW_IDX)(RHIIdxBuffer);
ANCIAPI ANCI_RHI_DRAW_IDX ANCIRHIDRAWIDX;
#define RHIDrawIdx ANCIRHIDRAWIDX
typedef RHIShader (*ANCI_RHI_CREATE_SHADER)(const char* source, RHIEnumCreateShaderMode mode);
ANCIAPI ANCI_RHI_CREATE_SHADER ANCIRHICreateShader;
#define RHICreateShader ANCIRHICreateShader

/**
 * 加载对应的API函数
 */
ANCIAPI void RHIApiLoad();