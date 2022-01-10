/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#pragma once

#include <AnciCore.h>

#ifndef RHIVtxBuffer
  typedef void * RHIVtxBuffer;
#endif

#ifndef RHIIdxBuffer
  typedef void * RHIIdxBuffer;
#endif

enum RHIEnumCreateShaderMode {
        RHI_VERTEX_SHADER,
        RHI_FRAGMENT_SHADER,
};

enum RHIEnumPolygonMode {
        RHI_POLYGON_MODE_FILL,
        RHI_POLYGON_MODE_POINT,
        RHI_POLYGON_MODE_LINE,
};

/* 顶点数据布局 */
struct RHIVtxArray {
        ancivec3 pos;
        ancivec3 color;
        ancivec2 uv;
        ancivec3 normal;
};

/* Shader对象，纯虚函数工具 */
class VRHIShader {
public:
        virtual void Bind     ()                                   = 0;
        virtual void SetInt   (const char *name, int      value)   = 0;
        virtual void SetFloat (const char *name, float    value)   = 0;
        virtual void SetFloat2(const char *name, ancivec2 value)   = 0;
        virtual void SetFloat3(const char *name, ancivec3 value)   = 0;
        virtual void SetFloat4(const char *name, ancivec4 value)   = 0;
        virtual void SetMat3  (const char *name, ancimat3 value)   = 0;
        virtual void SetMat4  (const char *name, ancimat4 value)   = 0;
};
typedef VRHIShader * RHIShader;

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
typedef RHIVtxBuffer (*ANCI_RHI_GEN_VTXBUFFER)(RHIVtxArray *vertices, anciu32 count);
ANCIAPI ANCI_RHI_GEN_VTXBUFFER ANCIRHIGENVTXBUFFER;
#define RHIGenVtxBuffer ANCIRHIGENVTXBUFFER
typedef RHIIdxBuffer (*ANCI_RHI_GEN_IDXBUFFER)(anciu32 *indices, anciu32 count);
ANCIAPI ANCI_RHI_GEN_IDXBUFFER ANCIRHIGENIDXBUFFER;
#define RHIGenIdxBuffer ANCIRHIGENIDXBUFFER
typedef void (*ANCI_RHI_DESTROY_VTX_BUFFER)(RHIVtxBuffer);
ANCIAPI ANCI_RHI_DESTROY_VTX_BUFFER ANCIRHIDELETEVTXBUFFER;
#define RHIDeleteVtxBuffer ANCIRHIDELETEVTXBUFFER
typedef void (*ANCI_RHI_DESTROY_IDX_BUFFER)(RHIIdxBuffer);
ANCIAPI ANCI_RHI_DESTROY_IDX_BUFFER ANCIRHIDELETEIDXBUFFER;
#define RHIDeleteIdxBuffer ANCIRHIDELETEIDXBUFFER
typedef void (*ANCI_RHI_BIND_VTX)(RHIVtxBuffer);
ANCIAPI ANCI_RHI_BIND_VTX ANCIRHIBINDVTX;
#define RHIBindVtxBuffer ANCIRHIBINDVTX
typedef void (*ANCI_RHI_DRAW_VTX)();
ANCIAPI ANCI_RHI_DRAW_VTX ANCIRHIDRAWVTX;
#define RHIDrawVtx ANCIRHIDRAWVTX
typedef void (*ANCI_RHI_DRAW_IDX)(RHIIdxBuffer);
ANCIAPI ANCI_RHI_DRAW_IDX ANCIRHIDRAWIDX;
#define RHIDrawIdx ANCIRHIDRAWIDX
typedef void (*ANCI_RHI_POLYGON_MODE)(RHIEnumPolygonMode);
ANCIAPI ANCI_RHI_POLYGON_MODE ANCIRHIPOLYGONMODE;
#define RHIPolygonMode ANCIRHIPOLYGONMODE
typedef RHIShader (*ANCI_RHI_CREATE_SHADER)(const char *alslFile);
ANCIAPI ANCI_RHI_CREATE_SHADER ANCIRHICREATESHADER;
#define RHICreateShader ANCIRHICREATESHADER
typedef void (*ANCI_RHI_DELETE_SHADER)(RHIShader);
ANCIAPI ANCI_RHI_DELETE_SHADER ANCIRHIDELETESHADER;
#define RHIDeleteShader ANCIRHIDELETESHADER
#define RHIBindShaderProgram ANCIRHIBINDSHADERPROGRAM
typedef void (*ANCI_RHI_CLEAR_COLOR_BUFFER)(ancivec4 color);
ANCIAPI ANCI_RHI_CLEAR_COLOR_BUFFER ANCIRHICLEARCOLORBUFFER;
#define RHIClearColorBuffer ANCIRHICLEARCOLORBUFFER

/**
 * 加载对应的API函数
 */
ANCIAPI void RHIApiLoad();