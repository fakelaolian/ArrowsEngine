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

typedef enum RHIKeyCodeBits {
        /* Printable keys */
        RHI_KEY_SPACE              = 32,
        RHI_KEY_APOSTROPHE         = 39,  /* ' */
        RHI_KEY_COMMA              = 44,  /* , */
        RHI_KEY_MINUS              = 45,  /* - */
        RHI_KEY_PERIOD             = 46,  /* . */
        RHI_KEY_SLASH              = 47,  /* / */
        RHI_KEY_0                  = 48,
        RHI_KEY_1                  = 49,
        RHI_KEY_2                  = 50,
        RHI_KEY_3                  = 51,
        RHI_KEY_4                  = 52,
        RHI_KEY_5                  = 53,
        RHI_KEY_6                  = 54,
        RHI_KEY_7                  = 55,
        RHI_KEY_8                  = 56,
        RHI_KEY_9                  = 57,
        RHI_KEY_SEMICOLON          = 59,  /* ; */
        RHI_KEY_EQUAL              = 61,  /* = */
        RHI_KEY_A                  = 65,
        RHI_KEY_B                  = 66,
        RHI_KEY_C                  = 67,
        RHI_KEY_D                  = 68,
        RHI_KEY_E                  = 69,
        RHI_KEY_F                  = 70,
        RHI_KEY_G                  = 71,
        RHI_KEY_H                  = 72,
        RHI_KEY_I                  = 73,
        RHI_KEY_J                  = 74,
        RHI_KEY_K                  = 75,
        RHI_KEY_L                  = 76,
        RHI_KEY_M                  = 77,
        RHI_KEY_N                  = 78,
        RHI_KEY_O                  = 79,
        RHI_KEY_P                  = 80,
        RHI_KEY_Q                  = 81,
        RHI_KEY_R                  = 82,
        RHI_KEY_S                  = 83,
        RHI_KEY_T                  = 84,
        RHI_KEY_U                  = 85,
        RHI_KEY_V                  = 86,
        RHI_KEY_W                  = 87,
        RHI_KEY_X                  = 88,
        RHI_KEY_Y                  = 89,
        RHI_KEY_Z                  = 90,
        RHI_KEY_LEFT_BRACKET       = 91,  /* [ */
        RHI_KEY_BACKSLASH          = 92,  /* \ */
        RHI_KEY_RIGHT_BRACKET      = 93,  /* ] */
        RHI_KEY_GRAVE_ACCENT       = 96,  /* ` */
        RHI_KEY_WORLD_1            = 161, /* non-US #1 */
        RHI_KEY_WORLD_2            = 162, /* non-US #2 */

        /* Function keys */
        RHI_KEY_ESCAPE             = 256,
        RHI_KEY_ENTER              = 257,
        RHI_KEY_TAB                = 258,
        RHI_KEY_BACKSPACE          = 259,
        RHI_KEY_INSERT             = 260,
        RHI_KEY_DELETE             = 261,
        RHI_KEY_RIGHT              = 262,
        RHI_KEY_LEFT               = 263,
        RHI_KEY_DOWN               = 264,
        RHI_KEY_UP                 = 265,
        RHI_KEY_PAGE_UP            = 266,
        RHI_KEY_PAGE_DOWN          = 267,
        RHI_KEY_HOME               = 268,
        RHI_KEY_END                = 269,
        RHI_KEY_CAPS_LOCK          = 280,
        RHI_KEY_SCROLL_LOCK        = 281,
        RHI_KEY_NUM_LOCK           = 282,
        RHI_KEY_PRINT_SCREEN       = 283,
        RHI_KEY_PAUSE              = 284,
        RHI_KEY_F1                 = 290,
        RHI_KEY_F2                 = 291,
        RHI_KEY_F3                 = 292,
        RHI_KEY_F4                 = 293,
        RHI_KEY_F5                 = 294,
        RHI_KEY_F6                 = 295,
        RHI_KEY_F7                 = 296,
        RHI_KEY_F8                 = 297,
        RHI_KEY_F9                 = 298,
        RHI_KEY_F10                = 299,
        RHI_KEY_F11                = 300,
        RHI_KEY_F12                = 301,
        RHI_KEY_F13                = 302,
        RHI_KEY_F14                = 303,
        RHI_KEY_F15                = 304,
        RHI_KEY_F16                = 305,
        RHI_KEY_F17                = 306,
        RHI_KEY_F18                = 307,
        RHI_KEY_F19                = 308,
        RHI_KEY_F20                = 309,
        RHI_KEY_F21                = 310,
        RHI_KEY_F22                = 311,
        RHI_KEY_F23                = 312,
        RHI_KEY_F24                = 313,
        RHI_KEY_F25                = 314,
        RHI_KEY_KP_0               = 320,
        RHI_KEY_KP_1               = 321,
        RHI_KEY_KP_2               = 322,
        RHI_KEY_KP_3               = 323,
        RHI_KEY_KP_4               = 324,
        RHI_KEY_KP_5               = 325,
        RHI_KEY_KP_6               = 326,
        RHI_KEY_KP_7               = 327,
        RHI_KEY_KP_8               = 328,
        RHI_KEY_KP_9               = 329,
        RHI_KEY_KP_DECIMAL         = 330,
        RHI_KEY_KP_DIVIDE          = 331,
        RHI_KEY_KP_MULTIPLY        = 332,
        RHI_KEY_KP_SUBTRACT        = 333,
        RHI_KEY_KP_ADD             = 334,
        RHI_KEY_KP_ENTER           = 335,
        RHI_KEY_KP_EQUAL           = 336,
        RHI_KEY_LEFT_SHIFT         = 340,
        RHI_KEY_LEFT_CONTROL       = 341,
        RHI_KEY_LEFT_ALT           = 342,
        RHI_KEY_LEFT_SUPER         = 343,
        RHI_KEY_RIGHT_SHIFT        = 344,
        RHI_KEY_RIGHT_CONTROL      = 345,
        RHI_KEY_RIGHT_ALT          = 346,
        RHI_KEY_RIGHT_SUPER        = 347,
        RHI_KEY_MENU               = 348,
} RHIKeyCodeBits;

typedef enum RHIGetKeyMode {
        RHI_PRESS                  = 0,
        RHI_RELEASE                = 1
} RHIGetKeyMode;

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

typedef enum RHIEnableBits {
        RHI_DEPTH_TEST
} RHIEnableBits;

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

typedef enum RHITextureWrapModeBits {
        RHI_TEXTURE_WRAP_REPEAT,
        RHI_TEXTURE_WRAP_MIRRORED_REPEAT,
        RHI_TEXTURE_WRAP_CLAMP_TO_EDGE,
        RHI_TEXTURE_WRAP_CLAMP_TO_BORDER
} RHITextureWrapModeBits;

typedef enum RHITextureFilterModeBits {
        RHI_TEXTURE_FILTER_NEAREST,
        RHI_TEXTURE_FILTER_LINEAR
} RHITextureFilterModeBits;

typedef struct RHITextureCreateInfo {
        RHIFormat format;
        anciu32 width;
        anciu32 height;
        RHITextureWrapModeBits textureWrapU;
        RHITextureWrapModeBits textureWrapV;
        RHITextureFilterModeBits textureFilterMin;
        RHITextureFilterModeBits textureFilterMag;
        anciuc *pPixels;
} RHITextureCreateInfo;

typedef struct RHIDimension2i {
        int x;
        int y;
} RHIDimension2i;

typedef struct RHIDimension2f {
        float x;
        float y;
} RHIDimension2f;

typedef enum RHIInputCursorModeBits{
        RHI_CURSOR_NORMAL,
        RHI_CURSOR_HIDDEN,
        RHI_CURSOR_DISABLE
} RHIInputCursorModeBits;

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
typedef void (*ANCI_RHI_DRAW_VTX)(anciu32 index, anciu32 offset);
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
typedef void (*ANCI_RHI_UNIFORM_FLOAT3V)(RHIShader, const char *name, float *);
ANCIAPI ANCI_RHI_UNIFORM_FLOAT3V ANCIRHIUNIFORMFLOAT3V;
#define RHIUniform3fv ANCIRHIUNIFORMFLOAT3V
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
typedef RHITexture (*ANCI_RHI_GEN_TEXTURE)(RHITextureCreateInfo *);
ANCIAPI ANCI_RHI_GEN_TEXTURE ANCIRHIGENTEXTURE;
#define RHIGenTexture ANCIRHIGENTEXTURE
typedef void (*ANCI_RHI_BIND_TEXTURE)(RHITexture);
ANCIAPI ANCI_RHI_BIND_TEXTURE ANCIRHIBINDTEXTURE;
#define RHIBindTexture ANCIRHIBINDTEXTURE
typedef void (*ANCI_RHI_DELETE_TEXTURE)(RHITexture);
ANCIAPI ANCI_RHI_DELETE_TEXTURE ANCIRHIDELETETEXTURE;
#define RHIDeleteTexture ANCIRHIDELETETEXTURE
typedef void (*ANCI_RHI_ENABLE)(RHIEnableBits, ancibool);
ANCIAPI ANCI_RHI_ENABLE ANCIRHIENABLE;
#define RHIEnable ANCIRHIENABLE

////////////////////////////////////////////////////////////////////////////////////
//////                              设备输入                                   //////
////////////////////////////////////////////////////////////////////////////////////
typedef RHIGetKeyMode (*ANCI_RHI_GET_KEY)(RHIWindow, RHIKeyCodeBits);
ANCIAPI ANCI_RHI_GET_KEY ANCIRHIGETKEY;
#define RHIGetKey ANCIRHIGETKEY
typedef void (*ANCI_RHI_SET_CURSOR_INPUT_MODE)(RHIWindow, RHIInputCursorModeBits);
ANCIAPI ANCI_RHI_SET_CURSOR_INPUT_MODE ANCIRHISETCURSORINPUTMODE;
#define RHISetCursorMode ANCIRHISETCURSORINPUTMODE

////////////////////////////////////////////////////////////////////////////////////
//////                    暴露给ImGui或者其他库使用                             //////
////////////////////////////////////////////////////////////////////////////////////
typedef RHIWindow (*ANCI_RHI_OPENGL_GET_CURRENT_CONTEXT)();
ANCIAPI ANCI_RHI_OPENGL_GET_CURRENT_CONTEXT ANCIRHIOPENGLGETCURRENTCONTEXT;
#define RHIGetCurrentContext_GL ANCIRHIOPENGLGETCURRENTCONTEXT
typedef void (*ANCI_RHI_OPENGL_MAKE_CONTEXT_CURRENT)(RHIWindow);
ANCIAPI ANCI_RHI_OPENGL_MAKE_CONTEXT_CURRENT ANCIRHIOPENGLMAKECONTEXTCURRENT;
#define RHIMakeContextCurrent_GL ANCIRHIOPENGLMAKECONTEXTCURRENT

////////////////////////////////////////////////////////////////////////////////////
//////                            和窗口有关的函数                             //////
////////////////////////////////////////////////////////////////////////////////////
typedef void (*F_RHI_WINDOW_RESIZE_CALLBACK)(RHIWindow, int, int);
typedef void (*F_RHI_WINDOW_CURSOR_CALLBACK)(RHIWindow, double, double);

typedef RHIWindow (*ANCI_RHI_CREATE_WINDOW)(const char *title, int width, int height);
ANCIAPI ANCI_RHI_CREATE_WINDOW ANCIRHICREATEWIDNOW;
#define RHICreateWindow ANCIRHICREATEWIDNOW
typedef void (*ANCI_RHI_WINDOW_POLL_EVENTS)();
ANCIAPI ANCI_RHI_WINDOW_POLL_EVENTS ANCIRHIWINDOWPOLLEVENTS;
#define RHIPollEvents ANCIRHIWINDOWPOLLEVENTS
typedef void (*ANCI_RHI_SET_USER_POINTER)(RHIWindow, void *);
ANCIAPI ANCI_RHI_SET_USER_POINTER ANCIRHISETUSERPOINTER;
#define RHISetUserPointer ANCIRHISETUSERPOINTER
typedef void * (*ANCI_RHI_GET_USER_POINTER)(RHIWindow);
ANCIAPI ANCI_RHI_GET_USER_POINTER ANCIRHIGETUSERPOINTER;
#define RHIGetUserPointer ANCIRHIGETUSERPOINTER
typedef ancibool (*ANCI_RHI_WINDOW_SHOULD_CLOSE)(RHIWindow);
ANCIAPI ANCI_RHI_WINDOW_SHOULD_CLOSE ANCIRHIWINDOWSHOULDCLOSE;
#define RHIWindowShouldClose ANCIRHIWINDOWSHOULDCLOSE
typedef void (*ANCI_RHI_WINDOW_SET_RESIZE_CALLBACK)(RHIWindow, F_RHI_WINDOW_RESIZE_CALLBACK);
ANCIAPI ANCI_RHI_WINDOW_SET_RESIZE_CALLBACK ANCIRHIWINDOWSETRESIZECALLBACK;
#define RHISetWindowResizeCallback ANCIRHIWINDOWSETRESIZECALLBACK
typedef void (*ANCI_RHI_WINDOW_SET_CURSOR_CALLBACK)(RHIWindow, F_RHI_WINDOW_CURSOR_CALLBACK);
ANCIAPI ANCI_RHI_WINDOW_SET_CURSOR_CALLBACK ANCIRHIWINDOWSETCURSORCALLBACK;
#define RHISetWindowCursorCallback ANCIRHIWINDOWSETCURSORCALLBACK
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