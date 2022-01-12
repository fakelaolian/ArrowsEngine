/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#ifndef _ANCI_RHI_H_
#define _ANCI_RHI_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void *          RHIWindow;
typedef void *          RHIVtxBuffer;
typedef void *          RHIIdxBuffer;
typedef void *          RHITexture;
typedef void *          RHIShader;

typedef unsigned char   anciuc;
typedef unsigned int    anciu32;
typedef unsigned long   anciu64;
typedef unsigned        ancibool;

#define RHI_TRUE        1U
#define RHI_FALSE       0U

#ifndef ANCIAPI
#  define ANCIAPI extern
#endif

/* 图形API选择枚举 */
typedef enum RHIGraphAPIBits {
        Vulkan,
        OpenGL,
        DX12
} RHIGraphAPIBits;

typedef enum RHIPolygonModeBits {
        RHI_POLYGON_MODE_FILL,
        RHI_POLYGON_MODE_POINT,
        RHI_POLYGON_MODE_LINE,
} RHIPolygonModeBits;

typedef enum RHIFormat {
        RHI_IMAGE_FORMAT_RGB,
        RHI_IMAGE_FORMAT_RGBA,
        RHI_FLOAT,
} RHIFormat;

typedef struct RHIVtxBufferLayout {
        anciu32 location;
        anciu32 size;
        RHIFormat format;
        anciu32 offset;
} RHIVtxBufferLayout;

typedef struct RHIVtxBufferCreateInfo {
        anciu32 vertexCount;
        RHIVtxBufferLayout *pBufferLayout;
        anciu32 bufferLayoutCount;
        anciu32 stride;
} RHIVtxBufferCreateInfo;

typedef struct RHIDimension {
        int x;
        int y;
} RHIDimension;

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
 *
 *
 *  列表：
 *      float           RHIGetTime              (void)
 *      void            RHIViewport             (anciu32 x, anciu32 y, anciu32 w, anciu32 h)
 *      void            RHISwapBuffers          (RHIWindow h)
 *      void            RHIGenVtxBuffer         (const void *pVertices, RHIVtxBufferCreateInfo *createInfo)
 *      void            RHIGenIdxBuffer         (anciu32 *indices, anciu32 count)
 *      void            RHIDeleteVtxBuffer      (RHIVtxBuffer)
 *      void            RHIDeleteIdxBuffer      (RHIIdxBuffer)
 *      void            RHIBindVtxBuffer        (RHIVtxBuffer)
 *      void            RHIDrawVtx              (void)
 *      void            RHIDrawIdx              (RHIIdxBuffer)
 *      void            RHIPolygonMode          (RHIPolygonModeBits)
 *      RHIShader       RHICreateShader         (const char *alslFile)
 *      void            RHIDeleteShader         (RHIShader)
 *      void            RHIClearColorBuffer     (float r, float g, float b, float a)
 *      RHITexture      RHIGenTexture           (RHIFormat format, anciu32 width, anciu32 height, anciuc *pixels)
 *      void            RHIBindTexture          (RHITexture)
 *      void            RHIDeleteTexture        (RHITexture)
 */
typedef float (*ANCI_RHI_GET_TIME)(void);
ANCIAPI ANCI_RHI_GET_TIME ANCIRHIGETTIME;
#define RHIGetTime ANCIRHIGETTIME
typedef void (*ANCI_RHI_VIEWPORT)(anciu32 x, anciu32 y, anciu32 w, anciu32 h);
ANCIAPI ANCI_RHI_VIEWPORT ANCIRHIVIEWPORT;
#define RHIViewport ANCIRHIVIEWPORT
typedef void (*ANCI_RHI_SWAP_BUFFERS)(RHIWindow h);
ANCIAPI ANCI_RHI_SWAP_BUFFERS ANCIRHISWAPBUFFERS;
#define RHISwapBuffers ANCIRHISWAPBUFFERS
typedef RHIVtxBuffer (*ANCI_RHI_GEN_VTXBUFFER)(const void *pVertices, RHIVtxBufferCreateInfo *);
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
typedef void (*ANCI_RHI_POLYGON_MODE)(RHIPolygonModeBits);
ANCIAPI ANCI_RHI_POLYGON_MODE ANCIRHIPOLYGONMODE;
#define RHIPolygonMode ANCIRHIPOLYGONMODE
typedef RHIShader (*ANCI_RHI_CREATE_SHADER)(const char *alsl);
ANCIAPI ANCI_RHI_CREATE_SHADER ANCIRHICREATESHADER;
#define RHICreateShader ANCIRHICREATESHADER
typedef void (*ANCI_RHI_BIND_SHADER)(RHIShader);
ANCIAPI ANCI_RHI_BIND_SHADER ANCIRHIBINDSHADER;
#define RHIBindShader ANCIRHIBINDSHADER
typedef void (*ANCI_RHI_UNIFORM_FLOAT2)(RHIShader, const char *name, float x, float y);
ANCIAPI ANCI_RHI_UNIFORM_FLOAT2 ANCIRHIUNIFORMFLOAT2;
#define RHIUniform2f ANCIRHIUNIFORMFLOAT2
typedef void (*ANCI_RHI_UNIFORM_INT)(RHIShader, const char *name, int value);
ANCIAPI ANCI_RHI_UNIFORM_INT ANCIRHIUNIFORMINT;
#define RHIUniform1i ANCIRHIUNIFORMINT
typedef void (*ANCI_RHI_UNIFORM_FLOAT3)(RHIShader, const char *name, float x, float y, float z);
ANCIAPI ANCI_RHI_UNIFORM_FLOAT3 ANCIRHIUNIFORMFLOAT3;
#define RHIUniform3f ANCIRHIUNIFORMFLOAT3
typedef void (*ANCI_RHI_UNIFORM_FLOAT4)(RHIShader, const char *name, float x, float y, float z, float w);
ANCIAPI ANCI_RHI_UNIFORM_FLOAT4 ANCIRHIUNIFORMFLOAT4;
#define RHIUniform4f ANCIRHIUNIFORMFLOAT4
typedef void (*ANCI_RHI_UNIFORM_MATRIX2FV)(RHIShader, const char *name, float *matrix);
ANCIAPI ANCI_RHI_UNIFORM_MATRIX2FV ANCIRHIUNIFORMMATRIX2FV;
#define RHIUniformMatrix2fv ANCIRHIUNIFORMMATRIX2FV
typedef void (*ANCI_RHI_UNIFORM_MATRIX3FV)(RHIShader, const char *name, float *matrix);
ANCIAPI ANCI_RHI_UNIFORM_MATRIX3FV ANCIRHIUNIFORMMATRIX3FV;
#define RHIUniformMatrix3fv ANCIRHIUNIFORMMATRIX3FV
typedef void (*ANCI_RHI_UNIFORM_MATRIX4FV)(RHIShader shader, const char *name, float *matrix);
ANCIAPI ANCI_RHI_UNIFORM_MATRIX4FV ANCIRHIUNIFORMMATRIX4FV;
#define RHIUniformMatrix4fv ANCIRHIUNIFORMMATRIX4FV
typedef void (*ANCI_RHI_DELETE_SHADER)(RHIShader);
ANCIAPI ANCI_RHI_DELETE_SHADER ANCIRHIDELETESHADER;
#define RHIDeleteShader ANCIRHIDELETESHADER
typedef void (*ANCI_RHI_CLEAR_COLOR_BUFFER)(float r, float g, float b, float a);
ANCIAPI ANCI_RHI_CLEAR_COLOR_BUFFER ANCIRHICLEARCOLORBUFFER;
#define RHIClearColorBuffer ANCIRHICLEARCOLORBUFFER
typedef RHITexture (*ANCI_RHI_GEN_TEXTURE)(RHIFormat format, anciu32 width, anciu32 height, anciuc *pixels);
ANCIAPI ANCI_RHI_GEN_TEXTURE ANCIRHIGENTEXTURE;
#define RHIGenTexture ANCIRHIGENTEXTURE
typedef void (*ANCI_RHI_BIND_TEXTURE)(RHITexture);
ANCIAPI ANCI_RHI_BIND_TEXTURE ANCIRHIBINDTEXTURE;
#define RHIBindTexture ANCIRHIBINDTEXTURE
typedef void (*ANCI_RHI_DELETE_TEXTURE)(RHITexture);
ANCIAPI ANCI_RHI_DELETE_TEXTURE ANCIRHIDELETETEXTURE;
#define RHIDeleteTexture ANCIRHIDELETETEXTURE

////////////////////////////////////////////////////////////////////////////////////
//////                            和窗口有关的函数                              //////
////////////////////////////////////////////////////////////////////////////////////
typedef void (*F_RHI_WINDOW_RESIZE_CALLBACK)(RHIWindow, int, int);

typedef RHIWindow (*ANCI_RHI_CREATE_WINDOW)(const char *title, int width, int height);
ANCIAPI ANCI_RHI_CREATE_WINDOW ANCIRHICREATEWIDNOW;
#define RHICreateWindow ANCIRHICREATEWIDNOW
typedef void (*ANCI_RHI_WINDOW_POLL_EVENTS)();
ANCIAPI ANCI_RHI_WINDOW_POLL_EVENTS ANCIRHIWINDOWPOLLEVENTS;
#define RHIPollEvents ANCIRHIWINDOWPOLLEVENTS
typedef ancibool (*ANCI_RHI_WINDOW_SHOULD_CLOSE)(RHIWindow);
ANCIAPI ANCI_RHI_WINDOW_SHOULD_CLOSE ANCIRHIWINDOWSHOULDCLOSE;
#define RHIWindowShouldClose ANCIRHIWINDOWSHOULDCLOSE
typedef void (*ANCI_RHI_WINDOW_SET_RESIZE_CALLBACK)(RHIWindow, F_RHI_WINDOW_RESIZE_CALLBACK);
ANCIAPI ANCI_RHI_WINDOW_SET_RESIZE_CALLBACK ANCIRHIWINDOWSETRESIZECALLBACK;
#define RHISetWindowResizeCallback ANCIRHIWINDOWSETRESIZECALLBACK
typedef void (*ANCI_RHI_DELETE_WINDOW)(RHIWindow);
ANCIAPI ANCI_RHI_DELETE_WINDOW ANCIRHIDELETWINDOW;
#define RHIDeleteWindow ANCIRHIDELETWINDOW

typedef void (*ANCI_RHI_TERMINATE)();
ANCIAPI ANCI_RHI_TERMINATE ANCIRHITERMINATE;
#define RHITerminate ANCIRHITERMINATE

/**
 * 加载对应的API函数
 */
ANCIAPI int RHIProcAddressInit(RHIGraphAPIBits);

#ifdef __cplusplus
}
#endif

#endif /*_ANCI_RHI_H_*/