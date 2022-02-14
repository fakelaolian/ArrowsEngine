/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#ifndef _ARS_H_
#define _ARS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char arsuc;
typedef unsigned int arsu32;
typedef unsigned arsbool;

typedef void *ArsWindow;
typedef void *ArsVertexBuffer;
typedef void *ArsIndicesBuffer;
typedef void *ArsTexture;
typedef void *ArsShader;
typedef void *ArsFramebuffer;
typedef arsu32 ArsID;

#define ARS_TRUE        1U
#define ARS_FALSE       0U

#define ARS_NULL_HANDLE NULL

#ifndef ARSAPI
#  define ARSAPI extern
#endif

typedef enum ArsKeyCodeBits {
    /* Printable keys */
    ARS_KEY_SPACE = 32,
    ARS_KEY_APOSTROPHE = 39,  /* ' */
    ARS_KEY_COMMA = 44,  /* , */
    ARS_KEY_MINUS = 45,  /* - */
    ARS_KEY_PERIOD = 46,  /* . */
    ARS_KEY_SLASH = 47,  /* / */
    ARS_KEY_0 = 48,
    ARS_KEY_1 = 49,
    ARS_KEY_2 = 50,
    ARS_KEY_3 = 51,
    ARS_KEY_4 = 52,
    ARS_KEY_5 = 53,
    ARS_KEY_6 = 54,
    ARS_KEY_7 = 55,
    ARS_KEY_8 = 56,
    ARS_KEY_9 = 57,
    ARS_KEY_SEMICOLON = 59,  /* ; */
    ARS_KEY_EQUAL = 61,  /* = */
    ARS_KEY_A = 65,
    ARS_KEY_B = 66,
    ARS_KEY_C = 67,
    ARS_KEY_D = 68,
    ARS_KEY_E = 69,
    ARS_KEY_F = 70,
    ARS_KEY_G = 71,
    ARS_KEY_H = 72,
    ARS_KEY_I = 73,
    ARS_KEY_J = 74,
    ARS_KEY_K = 75,
    ARS_KEY_L = 76,
    ARS_KEY_M = 77,
    ARS_KEY_N = 78,
    ARS_KEY_O = 79,
    ARS_KEY_P = 80,
    ARS_KEY_Q = 81,
    ARS_KEY_R = 82,
    ARS_KEY_S = 83,
    ARS_KEY_T = 84,
    ARS_KEY_U = 85,
    ARS_KEY_V = 86,
    ARS_KEY_W = 87,
    ARS_KEY_X = 88,
    ARS_KEY_Y = 89,
    ARS_KEY_Z = 90,
    ARS_KEY_LEFT_BRACKET = 91,  /* [ */
    ARS_KEY_BACKSLASH = 92,  /* \ */
    ARS_KEY_RIGHT_BRACKET = 93,  /* ] */
    ARS_KEY_GRAVE_ACCENT = 96,  /* ` */
    ARS_KEY_WORLD_1 = 161, /* non-US #1 */
    ARS_KEY_WORLD_2 = 162, /* non-US #2 */

    /* Function keys */
    ARS_KEY_ESCAPE = 256,
    ARS_KEY_ENTER = 257,
    ARS_KEY_TAB = 258,
    ARS_KEY_BACKSPACE = 259,
    ARS_KEY_INSERT = 260,
    ARS_KEY_DELETE = 261,
    ARS_KEY_RIGHT = 262,
    ARS_KEY_LEFT = 263,
    ARS_KEY_DOWN = 264,
    ARS_KEY_UP = 265,
    ARS_KEY_PAGE_UP = 266,
    ARS_KEY_PAGE_DOWN = 267,
    ARS_KEY_HOME = 268,
    ARS_KEY_END = 269,
    ARS_KEY_CAPS_LOCK = 280,
    ARS_KEY_SCROLL_LOCK = 281,
    ARS_KEY_NUM_LOCK = 282,
    ARS_KEY_PRINT_SCREEN = 283,
    ARS_KEY_PAUSE = 284,
    ARS_KEY_F1 = 290,
    ARS_KEY_F2 = 291,
    ARS_KEY_F3 = 292,
    ARS_KEY_F4 = 293,
    ARS_KEY_F5 = 294,
    ARS_KEY_F6 = 295,
    ARS_KEY_F7 = 296,
    ARS_KEY_F8 = 297,
    ARS_KEY_F9 = 298,
    ARS_KEY_F10 = 299,
    ARS_KEY_F11 = 300,
    ARS_KEY_F12 = 301,
    ARS_KEY_F13 = 302,
    ARS_KEY_F14 = 303,
    ARS_KEY_F15 = 304,
    ARS_KEY_F16 = 305,
    ARS_KEY_F17 = 306,
    ARS_KEY_F18 = 307,
    ARS_KEY_F19 = 308,
    ARS_KEY_F20 = 309,
    ARS_KEY_F21 = 310,
    ARS_KEY_F22 = 311,
    ARS_KEY_F23 = 312,
    ARS_KEY_F24 = 313,
    ARS_KEY_F25 = 314,
    ARS_KEY_KP_0 = 320,
    ARS_KEY_KP_1 = 321,
    ARS_KEY_KP_2 = 322,
    ARS_KEY_KP_3 = 323,
    ARS_KEY_KP_4 = 324,
    ARS_KEY_KP_5 = 325,
    ARS_KEY_KP_6 = 326,
    ARS_KEY_KP_7 = 327,
    ARS_KEY_KP_8 = 328,
    ARS_KEY_KP_9 = 329,
    ARS_KEY_KP_DECIMAL = 330,
    ARS_KEY_KP_DIVIDE = 331,
    ARS_KEY_KP_MULTIPLY = 332,
    ARS_KEY_KP_SUBTRACT = 333,
    ARS_KEY_KP_ADD = 334,
    ARS_KEY_KP_ENTER = 335,
    ARS_KEY_KP_EQUAL = 336,
    ARS_KEY_LEFT_SHIFT = 340,
    ARS_KEY_LEFT_CONTROL = 341,
    ARS_KEY_LEFT_ALT = 342,
    ARS_KEY_LEFT_SUPER = 343,
    ARS_KEY_RIGHT_SHIFT = 344,
    ARS_KEY_RIGHT_CONTROL = 345,
    ARS_KEY_RIGHT_ALT = 346,
    ARS_KEY_RIGHT_SUPER = 347,
    ARS_KEY_MENU = 348,
} ArsKeyCodeBits;

typedef enum ArsMouseButtonBits {
    ARS_MOUSE_BUTTON_1 = 0,
    ARS_MOUSE_BUTTON_2 = 1,
    ARS_MOUSE_BUTTON_3 = 2,
    ARS_MOUSE_BUTTON_4 = 3,
    ARS_MOUSE_BUTTON_5 = 4,
    ARS_MOUSE_BUTTON_6 = 5,
    ARS_MOUSE_BUTTON_7 = 6,
    ARS_MOUSE_BUTTON_8 = 7,
} ArsMouseButtonBits;

typedef enum ArsKeyModeBits {
    ARS_RELEASE = 0,
    ARS_PRESS = 1,
} ArsKeyModeBits;

/* 图形API选择枚举 */
typedef enum ArsGraphAPIBits {
    Vulkan,
    OpenGL,
    DX12
} ArsGraphAPIBits;

typedef enum ArsPolygonModeBits {
    ARS_POLYGON_MODE_FILL,
    ARS_POLYGON_MODE_POINT,
    ARS_POLYGON_MODE_LINE,
} ArsPolygonModeBits;

typedef enum ArsFormat {
    ARS_IMAGE_FORMAT_RGB,
    ARS_IMAGE_FORMAT_RGBA,
    ARS_IMAGE_FORMAT_RED,
    ARS_IMAGE_FORMAT_ALPHA,
    ARS_IMAGE_FORMAT_SRGB,
    ARS_IMAGE_FORMAT_SRGB8,
    ARS_TYPE_FORMAT_FLOAT,
} ArsFormat;

typedef enum ArsEnableBits {
    ARS_DEPTH_TEST
} ArsEnableBits;

typedef struct ArsVertexBufferLayout {
    arsu32 location;
    arsu32 size;
    ArsFormat format;
    arsu32 offset;
} ArsVertexBufferLayout;

typedef struct ArsVertexBufferMemLayoutInfo {
    arsu32 vertexCount;
    ArsVertexBufferLayout *pBufferLayout;
    arsu32 bufferLayoutCount;
    arsu32 stride;
    const void *pVertices;
} ArsVertexBufferMemLayoutInfo;

typedef enum ArsTextureWrapModeBits {
    ARS_TEXTURE_WRAP_NONE,
    ARS_TEXTURE_WRAP_REPEAT,
    ARS_TEXTURE_WRAP_MIRRORED_REPEAT,
    ARS_TEXTURE_WRAP_CLAMP_TO_EDGE,
    ARS_TEXTURE_WRAP_CLAMP_TO_BORDER
} ArsTextureWrapModeBits;

typedef enum ArsTextureFilterModeBits {
    ARS_TEXTURE_FILTER_NEAREST,
    ARS_TEXTURE_FILTER_LINEAR,
    ARS_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR,
} ArsTextureFilterModeBits;

typedef struct ArsTexture2DCreateInfo {
    arsu32 width;
    arsu32 height;
    ArsFormat format;
    ArsTextureWrapModeBits textureWrapS;
    ArsTextureWrapModeBits textureWrapT;
    ArsTextureFilterModeBits textureFilterMin;
    ArsTextureFilterModeBits textureFilterMag;
    arsuc *pPixels;
} ArsTexture2DCreateInfo;

typedef struct ArsTextureCubeCreateInfo {
    arsu32 width[6];
    arsu32 height[6];
    arsuc *pPixels[6];
    ArsFormat format[6];
    ArsTextureWrapModeBits textureWrapS;
    ArsTextureWrapModeBits textureWrapT;
    ArsTextureWrapModeBits textureWrapR;
    ArsTextureFilterModeBits textureFilterMin;
    ArsTextureFilterModeBits textureFilterMag;
} ArsTextureCubeCreateInfo;

typedef struct ArsDimension2i {
    int x;
    int y;
} ArsDimension2i;

typedef struct ArsDimension2f {
    float x;
    float y;
} ArsDimension2f;

typedef enum ArsInputCursorModeBits {
    ARS_CURSOR_NORMAL,
    ARS_CURSOR_HIDDEN,
    ARS_CURSOR_DISABLE
} ArsInputCursorModeBits;

typedef enum ArsTextureFormatBits {
    ARS_TEXTURE_2D,
    ARS_TEXTURE_CUBE_MAP,
} ArsTextureFormatBits;

typedef enum ArsDepthOptionBits {
    ARS_DEPTH_OPTION_ALWAYS,
    ARS_DEPTH_OPTION_NEVER,
    ARS_DEPTH_OPTION_EQ,
    ARS_DEPTH_OPTION_NE,
    ARS_DEPTH_OPTION_LT,
    ARS_DEPTH_OPTION_LE,
    ARS_DEPTH_OPTION_GT,
    ARS_DEPTH_OPTION_GE,
} ArsDepthOptionBits;

typedef struct ArsFramebufferCreateInfo {
    arsu32 width;
    arsu32 height;
} ArsFramebufferCreateInfo;

#define ARS_FRAMEBUFFER0 NULL

/**
 * Ars函数指针，命名规范：
 *      1. typedef <Result> <ARS_*>();
 *      2. 定义导出函数: ARSAPI <ARS_*> <变量名去掉函数指针命名的下划线>
 *      3. 定义宏，使用函数
 *
 * 示例：
 *      typedef void (*RHI_ARS_TEST)();
 *      ARSAPI RHI_ARS_TEST ARSTEST;
 *      #define ArsTest ARSTEST
 *
 *  列表：
 *      float           ArsGetTime                 (void)
 *      void            ArsViewport                (arsu32 x, arsu32 y, arsu32 w, arsu32 h)
 *      void            ArsSwapBuffers             (ArsWindow h)
 *      void            ArsCreateVertexBuffer         (const void *pVertices, ArsVertexBufferMemLayoutInfo *createInfo)
 *      void            ArsCreateIndicesBuffer         (arsu32 *indices, arsu32 count)
 *      void            ArsDestroyVertexBuffer     (ArsVertexBuffer)
 *      void            ArsDestroyIndicesBuffer    (ArsIndicesBuffer)
 *      void            ArsBindVertexBuffer        (ArsVertexBuffer)
 *      void            ArsDrawVtx                 (void)
 *      void            ArsDrawIndices             (ArsIndicesBuffer)
 *      void            ArsPolygonMode             (ArsPolygonModeBits)
 *      ArsShader       ArsCreateShader            (const char *alslFile)
 *      void            ArsDestroyShader           (ArsShader)
 *      void            ArsClearColorBuffer        (float r, float g, float b, float a)
 *      ArsTexture      ArsCreateTexture           (ArsFormat format, arsu32 width, arsu32 height, arsuc *pixels)
 *      void            ArsBindTexture             (ArsTexture)
 *      void            ArsDestroyTexture          (ArsTexture)
 */
typedef float (*RHI_ARS_GET_TIME)(void);
ARSAPI RHI_ARS_GET_TIME RHIARSGETTIME;
#define ArsGetTime RHIARSGETTIME
typedef void (*RHI_ARS_VIEWPORT)(arsu32 x, arsu32 y, arsu32 w, arsu32 h);
ARSAPI RHI_ARS_VIEWPORT RHIARSVIEWPORT;
#define ArsViewport RHIARSVIEWPORT
typedef void (*RHI_ARS_SWAP_BUFFERS)(ArsWindow h);
ARSAPI RHI_ARS_SWAP_BUFFERS RHIARSSWAPBUFFERS;
#define ArsSwapBuffers RHIARSSWAPBUFFERS
typedef void (*RHI_ARS_GEN_VTXBUFFER)(ArsVertexBufferMemLayoutInfo *, ArsVertexBuffer *);
ARSAPI RHI_ARS_GEN_VTXBUFFER RHIARSCREATEVTXBUFFER;
#define ArsCreateVertexBuffer RHIARSCREATEVTXBUFFER
typedef void (*RHI_ARS_GEN_IDXBUFFER)(arsu32 *indices, arsu32 count, ArsIndicesBuffer *);
ARSAPI RHI_ARS_GEN_IDXBUFFER RHIARSCREATEIDXBUFFER;
#define ArsCreateIndicesBuffer RHIARSCREATEIDXBUFFER
typedef void (*RHI_ARS_DESTROY_VTX_BUFFER)(ArsVertexBuffer);
ARSAPI RHI_ARS_DESTROY_VTX_BUFFER RHIARSDESTROYVTXBUFFER;
#define ArsDestroyVertexBuffer RHIARSDESTROYVTXBUFFER
typedef void (*RHI_ARS_DESTROY_IDX_BUFFER)(ArsIndicesBuffer);
ARSAPI RHI_ARS_DESTROY_IDX_BUFFER RHIARSDESTROYIDXBUFFER;
#define ArsDestroyIndicesBuffer RHIARSDESTROYIDXBUFFER
typedef void (*RHI_ARS_BIND_VTX)(ArsVertexBuffer);
ARSAPI RHI_ARS_BIND_VTX RHIARSBINDVTX;
#define ArsBindVertexBuffer RHIARSBINDVTX
typedef void (*RHI_ARS_DRAW_VTX)(arsu32 index, arsu32 offset);
ARSAPI RHI_ARS_DRAW_VTX RHIARSDRAWVTX;
#define ArsDrawVtx RHIARSDRAWVTX
typedef void (*RHI_ARS_DRAW_IDX)(ArsIndicesBuffer);
ARSAPI RHI_ARS_DRAW_IDX RHIARSDRAWIDX;
#define ArsDrawIndices RHIARSDRAWIDX
typedef void (*RHI_ARS_POLYGON_MODE)(ArsPolygonModeBits);
ARSAPI RHI_ARS_POLYGON_MODE RHIARSPOLYGONMODE;
#define ArsPolygonMode RHIARSPOLYGONMODE
typedef ArsShader (*RHI_ARS_CREATE_SHADER)(const char *alsl);
ARSAPI RHI_ARS_CREATE_SHADER RHIARSCREATESHADER;
#define ArsCreateShader RHIARSCREATESHADER
typedef void (*RHI_ARS_BIND_SHADER)(ArsShader);
ARSAPI RHI_ARS_BIND_SHADER RHIARSBINDSHADER;
#define ArsBindShader RHIARSBINDSHADER
typedef void (*RHI_ARS_UNIFORM_FLOAT1)(ArsShader, const char *name, float x);
ARSAPI RHI_ARS_UNIFORM_FLOAT1 RHIARSUNIFORMFLOAT1;
#define ArsUniform1f RHIARSUNIFORMFLOAT1
typedef void (*RHI_ARS_UNIFORM_FLOAT2)(ArsShader, const char *name, float x, float y);
ARSAPI RHI_ARS_UNIFORM_FLOAT2 RHIARSUNIFORMFLOAT2;
#define ArsUniform2f RHIARSUNIFORMFLOAT2
typedef void (*RHI_ARS_UNIFORM_INT)(ArsShader, const char *name, int value);
ARSAPI RHI_ARS_UNIFORM_INT RHIARSUNIFORMINT;
#define ArsUniform1i RHIARSUNIFORMINT
typedef void (*RHI_ARS_UNIFORM_FLOAT3)(ArsShader, const char *name, float x, float y, float z);
ARSAPI RHI_ARS_UNIFORM_FLOAT3 RHIARSUNIFORMFLOAT3;
#define ArsUniform3f RHIARSUNIFORMFLOAT3
typedef void (*RHI_ARS_UNIFORM_FLOAT3V)(ArsShader, const char *name, float *);
ARSAPI RHI_ARS_UNIFORM_FLOAT3V RHIARSUNIFORMFLOAT3V;
#define ArsUniform3fv RHIARSUNIFORMFLOAT3V
typedef void (*RHI_ARS_UNIFORM_FLOAT4)(ArsShader, const char *name, float x, float y, float z, float w);
ARSAPI RHI_ARS_UNIFORM_FLOAT4 RHIARSUNIFORMFLOAT4;
#define ArsUniform4f RHIARSUNIFORMFLOAT4
typedef void (*RHI_ARS_UNIFORM_MATRIX2FV)(ArsShader, const char *name, float *matrix);
ARSAPI RHI_ARS_UNIFORM_MATRIX2FV RHIARSUNIFORMMATRIX2FV;
#define ArsUniformMatrix2fv RHIARSUNIFORMMATRIX2FV
typedef void (*RHI_ARS_UNIFORM_MATRIX3FV)(ArsShader, const char *name, float *matrix);
ARSAPI RHI_ARS_UNIFORM_MATRIX3FV RHIARSUNIFORMMATRIX3FV;
#define ArsUniformMatrix3fv RHIARSUNIFORMMATRIX3FV
typedef void (*RHI_ARS_UNIFORM_MATRIX4FV)(ArsShader shader, const char *name, float *matrix);
ARSAPI RHI_ARS_UNIFORM_MATRIX4FV RHIARSUNIFORMMATRIX4FV;
#define ArsUniformMatrix4fv RHIARSUNIFORMMATRIX4FV
typedef void (*RHI_ARS_DELETE_SHADER)(ArsShader);
ARSAPI RHI_ARS_DELETE_SHADER RHIARSDESTROYSHADER;
#define ArsDestroyShader RHIARSDESTROYSHADER
typedef void (*RHI_ARS_CLEAR_COLOR_BUFFER)(float r, float g, float b, float a);
ARSAPI RHI_ARS_CLEAR_COLOR_BUFFER RHIARSCLEARCOLORBUFFER;
#define ArsClearColorBuffer RHIARSCLEARCOLORBUFFER
typedef void (*RHI_ARS_GEN_TEXTURE2D)(ArsTexture2DCreateInfo *, ArsTexture *);
ARSAPI RHI_ARS_GEN_TEXTURE2D RHIARSCREATETEXTURE2D;
#define ArsCreateTexture2D RHIARSCREATETEXTURE2D
typedef void (*RHI_ARS_DELETE_TEXTURE)(ArsTexture);
ARSAPI RHI_ARS_DELETE_TEXTURE RHIARSDESTROYTEXTURE;
#define ArsDestroyTexture RHIARSDESTROYTEXTURE
typedef void (*RHI_ARS_ENABLE)(ArsEnableBits, arsbool);
ARSAPI RHI_ARS_ENABLE RHIARSENABLE;
#define ArsEnable RHIARSENABLE
typedef ArsID (*RHI_ARS_GET_TEXTURE_ID)(ArsTexture);
ARSAPI RHI_ARS_GET_TEXTURE_ID RHIARSGETTEXTUREID;
#define ArsGetTextureId RHIARSGETTEXTUREID
typedef void (*RHI_ARS_BIND_TEXTURE)(ArsTextureFormatBits, ArsTexture);
ARSAPI RHI_ARS_BIND_TEXTURE RHIARSBINDTEXTURE;
#define ArsBindTexture RHIARSBINDTEXTURE
typedef void (*RHI_ARS_RESET_ACTIVE_TEXTURE)();
ARSAPI RHI_ARS_RESET_ACTIVE_TEXTURE RHIARSRESETACTIVETEXTURE;
#define ArsResetActiveTexture RHIARSRESETACTIVETEXTURE
typedef void (*RHI_ARS_CREATE_TEXTURE_CUBE_MAP)(ArsTextureCubeCreateInfo *, ArsTexture *);
ARSAPI RHI_ARS_CREATE_TEXTURE_CUBE_MAP RHIARSCREATETEXTURECUBEMAP;
#define ArsCreateTextureCubeMap RHIARSCREATETEXTURECUBEMAP
typedef void (*RHI_ARS_DEPTH_OPTION)(ArsDepthOptionBits);
ARSAPI RHI_ARS_DEPTH_OPTION RHIARSDEPTHOPTION;
#define ArsDepthOption RHIARSDEPTHOPTION
typedef arsbool (*RHI_ARS_CREATE_FRAMEBUFFER)(ArsFramebufferCreateInfo *createInfo, ArsFramebuffer *buffer);
ARSAPI RHI_ARS_CREATE_FRAMEBUFFER RHIARSCREATEFRAMEBUFFER;
#define ArsCreateFramebuffer RHIARSCREATEFRAMEBUFFER
typedef void (*RHI_ARS_RECREATE_FRAMEBUFFER)(ArsFramebufferCreateInfo *createInfo, ArsFramebuffer *buffer);
ARSAPI RHI_ARS_RECREATE_FRAMEBUFFER RHIARSRECREATEFRAMEBUFFER;
#define ArsRecreateFramebuffer RHIARSRECREATEFRAMEBUFFER
typedef void (*RHI_ARS_BIND_FRAMEBUFFER)(ArsFramebuffer);
ARSAPI RHI_ARS_BIND_FRAMEBUFFER RHIARSBINDFRAMEBUFFER;
#define ArsBindFramebuffer RHIARSBINDFRAMEBUFFER
typedef ArsTexture (*RHI_ARS_GET_FRAMEBUFFER_TEXTURE)(ArsFramebuffer);
ARSAPI RHI_ARS_GET_FRAMEBUFFER_TEXTURE RHIARSGETFRAMEBUFFERTEXTURE;
#define ArsGetFramebufferTexture RHIARSGETFRAMEBUFFERTEXTURE
typedef void (*RHI_ARS_DELETE_FRAMEBUFFER)(ArsFramebuffer);
ARSAPI RHI_ARS_DELETE_FRAMEBUFFER RHIARSDELETEFRAMEBUFFER;
#define ArsDeleteFramebuffer RHIARSDELETEFRAMEBUFFER

////////////////////////////////////////////////////////////////////////////////////
//////                              设备输入                                   //////
////////////////////////////////////////////////////////////////////////////////////
typedef ArsKeyModeBits (*RHI_ARS_GET_KEY)(ArsWindow, ArsKeyCodeBits);
ARSAPI RHI_ARS_GET_KEY RHIARSGETKEY;
#define ArsGetKey RHIARSGETKEY
typedef ArsKeyModeBits (*RHI_ARS_GET_MOUSE_BUTTON)(ArsWindow, ArsMouseButtonBits);
ARSAPI RHI_ARS_GET_MOUSE_BUTTON RHIARSGETMOUSEBUTTON;
#define ArsGetMouseButton RHIARSGETMOUSEBUTTON
typedef void (*RHI_ARS_SET_CURSOR_INPUT_MODE)(ArsWindow, ArsInputCursorModeBits);
ARSAPI RHI_ARS_SET_CURSOR_INPUT_MODE RHIARSSETCURSORINPUTMODE;
#define ArsSetCursorMode RHIARSSETCURSORINPUTMODE

////////////////////////////////////////////////////////////////////////////////////
//////                    暴露给ImGui或者其他库使用                             //////
////////////////////////////////////////////////////////////////////////////////////
typedef ArsWindow (*RHI_ARS_OPENGL_GET_CURRENT_CONTEXT)();
ARSAPI RHI_ARS_OPENGL_GET_CURRENT_CONTEXT RHIARSOPENGLGETCURRENTCONTEXT;
#define ArsGetCurrentContext_GL RHIARSOPENGLGETCURRENTCONTEXT
typedef void (*RHI_ARS_OPENGL_MAKE_CONTEXT_CURRENT)(ArsWindow);
ARSAPI RHI_ARS_OPENGL_MAKE_CONTEXT_CURRENT RHIARSOPENGLMAKECONTEXTCURRENT;
#define ArsMakeContextCurrent_GL RHIARSOPENGLMAKECONTEXTCURRENT

////////////////////////////////////////////////////////////////////////////////////
//////                            和窗口有关的函数                             //////
////////////////////////////////////////////////////////////////////////////////////
typedef void (*F_ARS_WINDOW_RESIZE_CALLBACK)(ArsWindow, int, int);
typedef void (*F_ARS_WINDOW_CURSOR_CALLBACK)(ArsWindow, double, double);

typedef void (*RHI_ARS_CREATE_WINDOW)(const char *title, int width, int height, ArsWindow *);
ARSAPI RHI_ARS_CREATE_WINDOW RHIARSCREATEWIDNOW;
#define ArsCreateWindow RHIARSCREATEWIDNOW
typedef void (*RHI_ARS_WINDOW_POLL_EVENTS)();
ARSAPI RHI_ARS_WINDOW_POLL_EVENTS RHIARSWINDOWPOLLEVENTS;
#define ArsPollEvents RHIARSWINDOWPOLLEVENTS
typedef void (*RHI_ARS_SET_USER_POINTER)(ArsWindow, void *);
ARSAPI RHI_ARS_SET_USER_POINTER RHIARSSETUSERPOINTER;
#define ArsSetUserPointer RHIARSSETUSERPOINTER
typedef void *(*RHI_ARS_GET_USER_POINTER)(ArsWindow);
ARSAPI RHI_ARS_GET_USER_POINTER RHIARSGETUSERPOINTER;
#define ArsGetUserPointer RHIARSGETUSERPOINTER
typedef arsbool (*RHI_ARS_WINDOW_SHOULD_CLOSE)(ArsWindow);
ARSAPI RHI_ARS_WINDOW_SHOULD_CLOSE RHIARSWINDOWSHOULDCLOSE;
#define ArsWindowShouldClose RHIARSWINDOWSHOULDCLOSE
typedef void (*RHI_ARS_WINDOW_SET_RESIZE_CALLBACK)(ArsWindow, F_ARS_WINDOW_RESIZE_CALLBACK);
ARSAPI RHI_ARS_WINDOW_SET_RESIZE_CALLBACK RHIARSWINDOWSETRESIZECALLBACK;
#define ArsSetWindowResizeCallback RHIARSWINDOWSETRESIZECALLBACK
typedef void (*RHI_ARS_WINDOW_SET_CURSOR_CALLBACK)(ArsWindow, F_ARS_WINDOW_CURSOR_CALLBACK);
ARSAPI RHI_ARS_WINDOW_SET_CURSOR_CALLBACK RHIARSWINDOWSETCURSORCALLBACK;
#define ArsSetWindowCursorCallback RHIARSWINDOWSETCURSORCALLBACK
typedef void (*RHI_ARS_DELETE_WINDOW)(ArsWindow);
ARSAPI RHI_ARS_DELETE_WINDOW RHIARSDELETWINDOW;
#define ArsDestroyWindow RHIARSDELETWINDOW
typedef void (*RHI_ARS_TERMINATE)();
ARSAPI RHI_ARS_TERMINATE RHIARSTERMINATE;
#define ArsTerminate RHIARSTERMINATE
typedef float (*RHI_ARS_GET_ASPECT)();
ARSAPI RHI_ARS_GET_ASPECT RHIARSGETASPECT;
#define ArsGetAspect RHIARSGETASPECT

/**
 * 加载对应的API函数
 */
ARSAPI int ArsProcAddressInit(ArsGraphAPIBits);

#ifdef __cplusplus
}
#endif

#endif /*_ARS_H_*/