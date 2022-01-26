/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#ifndef _ARS_H_
#define _ARS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char   arsuc;
typedef unsigned int    arsu32;
typedef unsigned long   arsu64;
typedef unsigned        arsbool;

typedef void *          ArsWindow;
typedef void *          ArsVertexBuffer;
typedef void *          ArsIndicesBuffer;
typedef void *          ArsTexture;
typedef void *          ArsShader;
typedef void *          ArsFramebuffer;
typedef arsu32         ArsID;

#define ARS_TRUE        1U
#define ARS_FALSE       0U

#ifndef ARS_API
#  define ARS_API extern
#endif

typedef enum ArsKeyCodeBits {
        /* Printable keys */
        ARS_KEY_SPACE              = 32,
        ARS_KEY_APOSTROPHE         = 39,  /* ' */
        ARS_KEY_COMMA              = 44,  /* , */
        ARS_KEY_MINUS              = 45,  /* - */
        ARS_KEY_PERIOD             = 46,  /* . */
        ARS_KEY_SLASH              = 47,  /* / */
        ARS_KEY_0                  = 48,
        ARS_KEY_1                  = 49,
        ARS_KEY_2                  = 50,
        ARS_KEY_3                  = 51,
        ARS_KEY_4                  = 52,
        ARS_KEY_5                  = 53,
        ARS_KEY_6                  = 54,
        ARS_KEY_7                  = 55,
        ARS_KEY_8                  = 56,
        ARS_KEY_9                  = 57,
        ARS_KEY_SEMICOLON          = 59,  /* ; */
        ARS_KEY_EQUAL              = 61,  /* = */
        ARS_KEY_A                  = 65,
        ARS_KEY_B                  = 66,
        ARS_KEY_C                  = 67,
        ARS_KEY_D                  = 68,
        ARS_KEY_E                  = 69,
        ARS_KEY_F                  = 70,
        ARS_KEY_G                  = 71,
        ARS_KEY_H                  = 72,
        ARS_KEY_I                  = 73,
        ARS_KEY_J                  = 74,
        ARS_KEY_K                  = 75,
        ARS_KEY_L                  = 76,
        ARS_KEY_M                  = 77,
        ARS_KEY_N                  = 78,
        ARS_KEY_O                  = 79,
        ARS_KEY_P                  = 80,
        ARS_KEY_Q                  = 81,
        ARS_KEY_R                  = 82,
        ARS_KEY_S                  = 83,
        ARS_KEY_T                  = 84,
        ARS_KEY_U                  = 85,
        ARS_KEY_V                  = 86,
        ARS_KEY_W                  = 87,
        ARS_KEY_X                  = 88,
        ARS_KEY_Y                  = 89,
        ARS_KEY_Z                  = 90,
        ARS_KEY_LEFT_BRACKET       = 91,  /* [ */
        ARS_KEY_BACKSLASH          = 92,  /* \ */
        ARS_KEY_RIGHT_BRACKET      = 93,  /* ] */
        ARS_KEY_GRAVE_ACCENT       = 96,  /* ` */
        ARS_KEY_WORLD_1            = 161, /* non-US #1 */
        ARS_KEY_WORLD_2            = 162, /* non-US #2 */

        /* Function keys */
        ARS_KEY_ESCAPE             = 256,
        ARS_KEY_ENTER              = 257,
        ARS_KEY_TAB                = 258,
        ARS_KEY_BACKSPACE          = 259,
        ARS_KEY_INSERT             = 260,
        ARS_KEY_DELETE             = 261,
        ARS_KEY_RIGHT              = 262,
        ARS_KEY_LEFT               = 263,
        ARS_KEY_DOWN               = 264,
        ARS_KEY_UP                 = 265,
        ARS_KEY_PAGE_UP            = 266,
        ARS_KEY_PAGE_DOWN          = 267,
        ARS_KEY_HOME               = 268,
        ARS_KEY_END                = 269,
        ARS_KEY_CAPS_LOCK          = 280,
        ARS_KEY_SCROLL_LOCK        = 281,
        ARS_KEY_NUM_LOCK           = 282,
        ARS_KEY_PRINT_SCREEN       = 283,
        ARS_KEY_PAUSE              = 284,
        ARS_KEY_F1                 = 290,
        ARS_KEY_F2                 = 291,
        ARS_KEY_F3                 = 292,
        ARS_KEY_F4                 = 293,
        ARS_KEY_F5                 = 294,
        ARS_KEY_F6                 = 295,
        ARS_KEY_F7                 = 296,
        ARS_KEY_F8                 = 297,
        ARS_KEY_F9                 = 298,
        ARS_KEY_F10                = 299,
        ARS_KEY_F11                = 300,
        ARS_KEY_F12                = 301,
        ARS_KEY_F13                = 302,
        ARS_KEY_F14                = 303,
        ARS_KEY_F15                = 304,
        ARS_KEY_F16                = 305,
        ARS_KEY_F17                = 306,
        ARS_KEY_F18                = 307,
        ARS_KEY_F19                = 308,
        ARS_KEY_F20                = 309,
        ARS_KEY_F21                = 310,
        ARS_KEY_F22                = 311,
        ARS_KEY_F23                = 312,
        ARS_KEY_F24                = 313,
        ARS_KEY_F25                = 314,
        ARS_KEY_KP_0               = 320,
        ARS_KEY_KP_1               = 321,
        ARS_KEY_KP_2               = 322,
        ARS_KEY_KP_3               = 323,
        ARS_KEY_KP_4               = 324,
        ARS_KEY_KP_5               = 325,
        ARS_KEY_KP_6               = 326,
        ARS_KEY_KP_7               = 327,
        ARS_KEY_KP_8               = 328,
        ARS_KEY_KP_9               = 329,
        ARS_KEY_KP_DECIMAL         = 330,
        ARS_KEY_KP_DIVIDE          = 331,
        ARS_KEY_KP_MULTIPLY        = 332,
        ARS_KEY_KP_SUBTRACT        = 333,
        ARS_KEY_KP_ADD             = 334,
        ARS_KEY_KP_ENTER           = 335,
        ARS_KEY_KP_EQUAL           = 336,
        ARS_KEY_LEFT_SHIFT         = 340,
        ARS_KEY_LEFT_CONTROL       = 341,
        ARS_KEY_LEFT_ALT           = 342,
        ARS_KEY_LEFT_SUPER         = 343,
        ARS_KEY_RIGHT_SHIFT        = 344,
        ARS_KEY_RIGHT_CONTROL      = 345,
        ARS_KEY_RIGHT_ALT          = 346,
        ARS_KEY_RIGHT_SUPER        = 347,
        ARS_KEY_MENU               = 348,
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
        ARS_RELEASE                = 0,
        ARS_PRESS                  = 1,
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
        ARS_TEXTURE_FILTER_LINEAR
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

typedef enum ArsInputCursorModeBits{
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
 *      2. 定义导出函数: ARS_API <ARS_*> <变量名去掉函数指针命名的下划线>
 *      3. 定义宏，使用函数
 *
 * 示例：
 *      typedef void (*ARS_TEST)();
 *      ARS_API ARS_TEST ARSTEST;
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
typedef float (*ARS_GET_TIME)(void);
ARS_API ARS_GET_TIME ARSGETTIME;
#define ArsGetTime ARSGETTIME
typedef void (*ARS_VIEWPORT)(arsu32 x, arsu32 y, arsu32 w, arsu32 h);
ARS_API ARS_VIEWPORT ARSVIEWPORT;
#define ArsViewport ARSVIEWPORT
typedef void (*ARS_SWAP_BUFFERS)(ArsWindow h);
ARS_API ARS_SWAP_BUFFERS ARSSWAPBUFFERS;
#define ArsSwapBuffers ARSSWAPBUFFERS
typedef void (*ARS_GEN_VTXBUFFER)(ArsVertexBufferMemLayoutInfo *, ArsVertexBuffer *);
ARS_API ARS_GEN_VTXBUFFER ARSCREATEVTXBUFFER;
#define ArsCreateVertexBuffer ARSCREATEVTXBUFFER
typedef void (*ARS_GEN_IDXBUFFER)(arsu32 *indices, arsu32 count, ArsIndicesBuffer *);
ARS_API ARS_GEN_IDXBUFFER ARSCREATEIDXBUFFER;
#define ArsCreateIndicesBuffer ARSCREATEIDXBUFFER
typedef void (*ARS_DESTROY_VTX_BUFFER)(ArsVertexBuffer);
ARS_API ARS_DESTROY_VTX_BUFFER ARSDESTROYVTXBUFFER;
#define ArsDestroyVertexBuffer ARSDESTROYVTXBUFFER
typedef void (*ARS_DESTROY_IDX_BUFFER)(ArsIndicesBuffer);
ARS_API ARS_DESTROY_IDX_BUFFER ARSDESTROYIDXBUFFER;
#define ArsDestroyIndicesBuffer ARSDESTROYIDXBUFFER
typedef void (*ARS_BIND_VTX)(ArsVertexBuffer);
ARS_API ARS_BIND_VTX ARSBINDVTX;
#define ArsBindVertexBuffer ARSBINDVTX
typedef void (*ARS_DRAW_VTX)(arsu32 index, arsu32 offset);
ARS_API ARS_DRAW_VTX ARSDRAWVTX;
#define ArsDrawVtx ARSDRAWVTX
typedef void (*ARS_DRAW_IDX)(ArsIndicesBuffer);
ARS_API ARS_DRAW_IDX ARSDRAWIDX;
#define ArsDrawIndices ARSDRAWIDX
typedef void (*ARS_POLYGON_MODE)(ArsPolygonModeBits);
ARS_API ARS_POLYGON_MODE ARSPOLYGONMODE;
#define ArsPolygonMode ARSPOLYGONMODE
typedef ArsShader (*ARS_CREATE_SHADER)(const char *alsl);
ARS_API ARS_CREATE_SHADER ARSCREATESHADER;
#define ArsCreateShader ARSCREATESHADER
typedef void (*ARS_BIND_SHADER)(ArsShader);
ARS_API ARS_BIND_SHADER ARSBINDSHADER;
#define ArsBindShader ARSBINDSHADER
typedef void (*ARS_UNIFORM_FLOAT1)(ArsShader, const char *name, float x);
ARS_API ARS_UNIFORM_FLOAT1 ARSUNIFORMFLOAT1;
#define ArsUniform1f ARSUNIFORMFLOAT1
typedef void (*ARS_UNIFORM_FLOAT2)(ArsShader, const char *name, float x, float y);
ARS_API ARS_UNIFORM_FLOAT2 ARSUNIFORMFLOAT2;
#define ArsUniform2f ARSUNIFORMFLOAT2
typedef void (*ARS_UNIFORM_INT)(ArsShader, const char *name, int value);
ARS_API ARS_UNIFORM_INT ARSUNIFORMINT;
#define ArsUniform1i ARSUNIFORMINT
typedef void (*ARS_UNIFORM_FLOAT3)(ArsShader, const char *name, float x, float y, float z);
ARS_API ARS_UNIFORM_FLOAT3 ARSUNIFORMFLOAT3;
#define ArsUniform3f ARSUNIFORMFLOAT3
typedef void (*ARS_UNIFORM_FLOAT3V)(ArsShader, const char *name, float *);
ARS_API ARS_UNIFORM_FLOAT3V ARSUNIFORMFLOAT3V;
#define ArsUniform3fv ARSUNIFORMFLOAT3V
typedef void (*ARS_UNIFORM_FLOAT4)(ArsShader, const char *name, float x, float y, float z, float w);
ARS_API ARS_UNIFORM_FLOAT4 ARSUNIFORMFLOAT4;
#define ArsUniform4f ARSUNIFORMFLOAT4
typedef void (*ARS_UNIFORM_MATRIX2FV)(ArsShader, const char *name, float *matrix);
ARS_API ARS_UNIFORM_MATRIX2FV ARSUNIFORMMATRIX2FV;
#define ArsUniformMatrix2fv ARSUNIFORMMATRIX2FV
typedef void (*ARS_UNIFORM_MATRIX3FV)(ArsShader, const char *name, float *matrix);
ARS_API ARS_UNIFORM_MATRIX3FV ARSUNIFORMMATRIX3FV;
#define ArsUniformMatrix3fv ARSUNIFORMMATRIX3FV
typedef void (*ARS_UNIFORM_MATRIX4FV)(ArsShader shader, const char *name, float *matrix);
ARS_API ARS_UNIFORM_MATRIX4FV ARSUNIFORMMATRIX4FV;
#define ArsUniformMatrix4fv ARSUNIFORMMATRIX4FV
typedef void (*ARS_DELETE_SHADER)(ArsShader);
ARS_API ARS_DELETE_SHADER ARSDESTROYSHADER;
#define ArsDestroyShader ARSDESTROYSHADER
typedef void (*ARS_CLEAR_COLOR_BUFFER)(float r, float g, float b, float a);
ARS_API ARS_CLEAR_COLOR_BUFFER ARSCLEARCOLORBUFFER;
#define ArsClearColorBuffer ARSCLEARCOLORBUFFER
typedef void (*ARS_GEN_TEXTURE2D)(ArsTexture2DCreateInfo *, ArsTexture *);
ARS_API ARS_GEN_TEXTURE2D ARSCREATETEXTURE2D;
#define ArsCreateTexture2D ARSCREATETEXTURE2D
typedef void (*ARS_DELETE_TEXTURE)(ArsTexture);
ARS_API ARS_DELETE_TEXTURE ARSDESTROYTEXTURE;
#define ArsDestroyTexture ARSDESTROYTEXTURE
typedef void (*ARS_ENABLE)(ArsEnableBits, arsbool);
ARS_API ARS_ENABLE ARSENABLE;
#define ArsEnable ARSENABLE
typedef ArsID (*ARS_GET_TEXTURE_ID)(ArsTexture);
ARS_API ARS_GET_TEXTURE_ID ARSGETTEXTUREID;
#define ArsGetTextureId ARSGETTEXTUREID
typedef void (*ARS_BIND_TEXTURE)(ArsTextureFormatBits, ArsTexture);
ARS_API ARS_BIND_TEXTURE ARSBINDTEXTURE;
#define ArsBindTexture ARSBINDTEXTURE
typedef void (*ARS_CREATE_TEXTURE_CUBE_MAP)(ArsTextureCubeCreateInfo *, ArsTexture *);
ARS_API ARS_CREATE_TEXTURE_CUBE_MAP ARSCREATETEXTURECUBEMAP;
#define ArsCreateTextureCubeMap ARSCREATETEXTURECUBEMAP
typedef void (*ARS_DEPTH_OPTION)(ArsDepthOptionBits);
ARS_API ARS_DEPTH_OPTION ARSDEPTHOPTION;
#define ArsDepthOption ARSDEPTHOPTION
typedef arsbool (*ARS_CREATE_FRAMEBUFFER)(ArsFramebufferCreateInfo *createInfo, ArsFramebuffer *buffer);
ARS_API ARS_CREATE_FRAMEBUFFER ARSCREATEFRAMEBUFFER;
#define ArsCreateFramebuffer ARSCREATEFRAMEBUFFER
typedef void (*ARS_RECREATE_FRAMEBUFFER)(ArsFramebufferCreateInfo *createInfo, ArsFramebuffer *buffer);
ARS_API ARS_RECREATE_FRAMEBUFFER ARSRECREATEFRAMEBUFFER;
#define ArsRecreateFramebuffer ARSRECREATEFRAMEBUFFER
typedef void (*ARS_BIND_FRAMEBUFFER)(ArsFramebuffer);
ARS_API ARS_BIND_FRAMEBUFFER ARSBINDFRAMEBUFFER;
#define ArsBindFramebuffer ARSBINDFRAMEBUFFER
typedef ArsTexture (*ARS_GET_FRAMEBUFFER_TEXTURE)(ArsFramebuffer);
ARS_API ARS_GET_FRAMEBUFFER_TEXTURE ARSGETFRAMEBUFFERTEXTURE;
#define ArsGetFramebufferTexture ARSGETFRAMEBUFFERTEXTURE
typedef void (*ARS_DELETE_FRAMEBUFFER)(ArsFramebuffer);
ARS_API ARS_DELETE_FRAMEBUFFER ARSDELETEFRAMEBUFFER;
#define ArsDeleteFramebuffer ARSDELETEFRAMEBUFFER

////////////////////////////////////////////////////////////////////////////////////
//////                              设备输入                                   //////
////////////////////////////////////////////////////////////////////////////////////
typedef ArsKeyModeBits (*ARS_GET_KEY)(ArsWindow, ArsKeyCodeBits);
ARS_API ARS_GET_KEY ARSGETKEY;
#define ArsGetKey ARSGETKEY
typedef ArsKeyModeBits (*ARS_GET_MOUSE_BUTTON)(ArsWindow, ArsMouseButtonBits);
ARS_API ARS_GET_MOUSE_BUTTON ARSGETMOUSEBUTTON;
#define ArsGetMouseButton ARSGETMOUSEBUTTON
typedef void (*ARS_SET_CURSOR_INPUT_MODE)(ArsWindow, ArsInputCursorModeBits);
ARS_API ARS_SET_CURSOR_INPUT_MODE ARSSETCURSORINPUTMODE;
#define ArsSetCursorMode ARSSETCURSORINPUTMODE

////////////////////////////////////////////////////////////////////////////////////
//////                    暴露给ImGui或者其他库使用                             //////
////////////////////////////////////////////////////////////////////////////////////
typedef ArsWindow (*ARS_OPENGL_GET_CURRENT_CONTEXT)();
ARS_API ARS_OPENGL_GET_CURRENT_CONTEXT ARSOPENGLGETCURRENTCONTEXT;
#define ArsGetCurrentContext_GL ARSOPENGLGETCURRENTCONTEXT
typedef void (*ARS_OPENGL_MAKE_CONTEXT_CURRENT)(ArsWindow);
ARS_API ARS_OPENGL_MAKE_CONTEXT_CURRENT ARSOPENGLMAKECONTEXTCURRENT;
#define ArsMakeContextCurrent_GL ARSOPENGLMAKECONTEXTCURRENT

////////////////////////////////////////////////////////////////////////////////////
//////                            和窗口有关的函数                             //////
////////////////////////////////////////////////////////////////////////////////////
typedef void (*F_ARS_WINDOW_RESIZE_CALLBACK)(ArsWindow, int, int);
typedef void (*F_ARS_WINDOW_CURSOR_CALLBACK)(ArsWindow, double, double);

typedef void (*ARS_CREATE_WINDOW)(const char *title, int width, int height, ArsWindow *);
ARS_API ARS_CREATE_WINDOW ARSCREATEWIDNOW;
#define ArsCreateWindow ARSCREATEWIDNOW
typedef void (*ARS_WINDOW_POLL_EVENTS)();
ARS_API ARS_WINDOW_POLL_EVENTS ARSWINDOWPOLLEVENTS;
#define ArsPollEvents ARSWINDOWPOLLEVENTS
typedef void (*ARS_SET_USER_POINTER)(ArsWindow, void *);
ARS_API ARS_SET_USER_POINTER ARSSETUSERPOINTER;
#define ArsSetUserPointer ARSSETUSERPOINTER
typedef void * (*ARS_GET_USER_POINTER)(ArsWindow);
ARS_API ARS_GET_USER_POINTER ARSGETUSERPOINTER;
#define ArsGetUserPointer ARSGETUSERPOINTER
typedef arsbool (*ARS_WINDOW_SHOULD_CLOSE)(ArsWindow);
ARS_API ARS_WINDOW_SHOULD_CLOSE ARSWINDOWSHOULDCLOSE;
#define ArsWindowShouldClose ARSWINDOWSHOULDCLOSE
typedef void (*ARS_WINDOW_SET_RESIZE_CALLBACK)(ArsWindow, F_ARS_WINDOW_RESIZE_CALLBACK);
ARS_API ARS_WINDOW_SET_RESIZE_CALLBACK ARSWINDOWSETRESIZECALLBACK;
#define ArsSetWindowResizeCallback ARSWINDOWSETRESIZECALLBACK
typedef void (*ARS_WINDOW_SET_CURSOR_CALLBACK)(ArsWindow, F_ARS_WINDOW_CURSOR_CALLBACK);
ARS_API ARS_WINDOW_SET_CURSOR_CALLBACK ARSWINDOWSETCURSORCALLBACK;
#define ArsSetWindowCursorCallback ARSWINDOWSETCURSORCALLBACK
typedef void (*ARS_DELETE_WINDOW)(ArsWindow);
ARS_API ARS_DELETE_WINDOW ARSDELETWINDOW;
#define ArsDestroyWindow ARSDELETWINDOW
typedef void (*ARS_TERMINATE)();
ARS_API ARS_TERMINATE ARSTERMINATE;
#define ArsTerminate ARSTERMINATE
typedef float (*ARS_GET_ASPECT)();
ARS_API ARS_GET_ASPECT ARSGETASPECT;
#define ArsGetAspect ARSGETASPECT

/**
 * 加载对应的API函数
 */
ARS_API int ArsProcAddressInit(ArsGraphAPIBits);

#ifdef __cplusplus
}
#endif

#endif /*_ARS_H_*/