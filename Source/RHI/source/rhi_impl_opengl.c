/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "RHI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "alsl.h"

ANCI_RHI_GET_TIME                       ANCIRHIGETTIME                    = NULL;
ANCI_RHI_VIEWPORT                       ANCIRHIVIEWPORT                   = NULL;
ANCI_RHI_SWAP_BUFFERS                   ANCIRHISWAPBUFFERS                = NULL;
ANCI_RHI_GEN_IDXBUFFER                  ANCIRHIGENIDXBUFFER               = NULL;
ANCI_RHI_GEN_VTXBUFFER                  ANCIRHIGENVTXBUFFER               = NULL;
ANCI_RHI_DESTROY_VTX_BUFFER             ANCIRHIDELETEVTXBUFFER            = NULL;
ANCI_RHI_DESTROY_IDX_BUFFER             ANCIRHIDELETEIDXBUFFER            = NULL;
ANCI_RHI_BIND_VTX                       ANCIRHIBINDVTX                    = NULL;
ANCI_RHI_DRAW_VTX                       ANCIRHIDRAWVTX                    = NULL;
ANCI_RHI_DRAW_IDX                       ANCIRHIDRAWIDX                    = NULL;
ANCI_RHI_POLYGON_MODE                   ANCIRHIPOLYGONMODE                = NULL;
ANCI_RHI_CREATE_SHADER                  ANCIRHICREATESHADER               = NULL;
ANCI_RHI_BIND_SHADER                    ANCIRHIBINDSHADER                 = NULL;
ANCI_RHI_UNIFORM_FLOAT2                 ANCIRHIUNIFORMFLOAT2              = NULL;
ANCI_RHI_UNIFORM_INT                    ANCIRHIUNIFORMINT                 = NULL;
ANCI_RHI_UNIFORM_FLOAT3                 ANCIRHIUNIFORMFLOAT3              = NULL;
ANCI_RHI_UNIFORM_FLOAT4                 ANCIRHIUNIFORMFLOAT4              = NULL;
ANCI_RHI_UNIFORM_MATRIX2FV              ANCIRHIUNIFORMMATRIX2FV           = NULL;
ANCI_RHI_UNIFORM_MATRIX3FV              ANCIRHIUNIFORMMATRIX3FV           = NULL;
ANCI_RHI_UNIFORM_MATRIX4FV              ANCIRHIUNIFORMMATRIX4FV           = NULL;
ANCI_RHI_DELETE_SHADER                  ANCIRHIDELETESHADER               = NULL;
ANCI_RHI_CLEAR_COLOR_BUFFER             ANCIRHICLEARCOLORBUFFER           = NULL;
ANCI_RHI_GEN_TEXTURE                    ANCIRHIGENTEXTURE                 = NULL;
ANCI_RHI_DELETE_TEXTURE                 ANCIRHIDELETETEXTURE              = NULL;
ANCI_RHI_BIND_TEXTURE                   ANCIRHIBINDTEXTURE                = NULL;

anciu32 _activeTexture                                                    = 0;

/** OpenGL的Vertex Buffer实现 */
typedef struct RHIVtxBufferGL {
        anciu32 vao;
        anciu32 vbo;
        anciu32 count;
} RHIVtxBufferGL;
#define IVtxBuffer RHIVtxBufferGL *
#define CONV_VTX(ptr) ((RHIVtxBufferGL *) (ptr))

/** OpenGL的Index Buffer实现 */
typedef struct RHIIdxBufferGL {
        anciu32 ebo;
        anciu32 count;
} RHIIdxBufferGL;
#define IIdxBuffer RHIIdxBufferGL *
#define CONV_IDX(ptr) ((RHIIdxBufferGL *) (ptr))

/** OpenGL的Texture实现 */
typedef struct RHITextureGL {
        anciu32 textureId;
        anciu32 width;
        anciu32 height;
} RHITextureGL;
#define ITexture RHITextureGL *
#define CONV_TEX(ptr) ((RHITextureGL *) (ptr))

/** OpenGL的Shader实现 */
typedef struct RHIShaderGL {
        anciu32 program;
} RHIShaderGL;
#define IShader RHIShaderGL *
#define CONV_SHADER(ptr) ((RHIShaderGL *) (ptr))

float GLFW_GetTime        () { return glfwGetTime(); }
void OpenGL_GLViewport    (anciu32 x, anciu32 y, anciu32 w, anciu32 h) { glViewport((GLint) x, (GLint) y, (GLsizei) w, (GLsizei) h); }
void OpenGL_GLSwapBuffers (RHIWindow h) { glfwSwapBuffers((GLFWwindow *) h); }

RHIVtxBuffer OpenGL_GenVtxBuffer(const void *pVertices, RHIVtxBufferCreateInfo *createInfo)
{
        anciu32 vao;
        anciu32 vbo;
        anciu32 i;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, createInfo->vertexCount * createInfo->stride, pVertices, GL_STATIC_DRAW);

        for (i = 0; i < createInfo->bufferLayoutCount; i++) {
                RHIVtxBufferLayout layout = createInfo->pBufferLayout[i];
                glEnableVertexAttribArray(layout.location);
                glVertexAttribPointer(layout.location, (int) layout.size, GL_FLOAT, GL_FALSE, (int) createInfo->stride, (void*) (size_t) layout.offset);
        }

        /* 解除绑定 */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        RHIVtxBufferGL *pVtxBuffer = vmalloc(sizeof(RHIVtxBufferGL));
        pVtxBuffer->vao = vao;
        pVtxBuffer->vbo = vbo;
        pVtxBuffer->count = createInfo->vertexCount / createInfo->stride;

        return pVtxBuffer;
}

RHIIdxBuffer OpenGL_GenIdxBuffer(anciu32 *indices, anciu32 count)
{
        unsigned int ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(anciu32), indices, GL_STATIC_DRAW);

        RHIIdxBufferGL *pIdxBuffer = vmalloc(sizeof(RHIIdxBufferGL));
        pIdxBuffer->ebo = ebo;
        pIdxBuffer->count = count;

        return pIdxBuffer;
}

void OpenGL_DestroyVtxBuffer(RHIVtxBuffer vtxBuffer)
{
        IVtxBuffer buffer = CONV_VTX(vtxBuffer);
        glDeleteVertexArrays(1, &buffer->vao);
        glDeleteBuffers(1, &buffer->vbo);

        vfree(buffer);
}

void OpenGL_DestroyIdxBuffer(RHIIdxBuffer idxBuffer)
{
        IIdxBuffer buffer = CONV_IDX(idxBuffer);
        glDeleteBuffers(1, &buffer->ebo);

        vfree(buffer);
}

void OpenGL_BindVtxBuffer(RHIVtxBuffer vtxBuffer)
{
        glBindVertexArray(CONV_VTX(vtxBuffer)->vao);
}

void OpenGL_DrawVtx()
{
        glDrawArrays(GL_TRIANGLES, 0, 3);
        _activeTexture = 0;
}

void OpenGL_DrawIdx(RHIIdxBuffer idxBuffer)
{
        IIdxBuffer buffer = CONV_IDX(idxBuffer);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->ebo);
        glDrawElements(GL_TRIANGLES, buffer->count, GL_UNSIGNED_INT, 0);
        _activeTexture = 0;
}

void OpenGL_PolygonMode(RHIPolygonModeBits mode)
{
        switch (mode) {
                case RHI_POLYGON_MODE_FILL:  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  break;
                case RHI_POLYGON_MODE_LINE:  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  break;
                case RHI_POLYGON_MODE_POINT: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
        }
}

RHIShader OpenGL_CreateShader(const char* file)
{
        anciu32         program;
        anciu32         vertex;
        anciu32         fragment;
        int             success;
        char            infoLog[512];
        ShaderSource    source;

        load_shader_source(file, &source);
        program = glCreateProgram();

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &source.vtx, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                printf("ERROR - 创建Shader失败： %s\n", infoLog);
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &source.frag, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(fragment, 512, NULL, infoLog);
                printf("ERROR - 创建Shader失败： %s\n", infoLog);
        }

        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success) {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                printf("ERROR - 创建Shader失败： %s\n", infoLog);
        }

        /* 删除shader以及源码 */
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        free_shader_source(&source);

        RHIShaderGL *pShaderGL = vmalloc(sizeof(RHIShaderGL));
        pShaderGL->program = program;

        return pShaderGL;
}

void OpenGL_BindShader(RHIShader shader)
{
        glUseProgram(CONV_SHADER(shader)->program);
}

void OpenGL_Uniform1i(RHIShader shader, const char *name, int value)
{
        glUniform1i(glGetUniformLocation(CONV_SHADER(shader)->program, name), value);
}

void OpenGL_Uniform2f(RHIShader shader, const char *name, float x, float y)
{
        glUniform2f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y);
}

void OpenGL_Uniform3f(RHIShader shader, const char *name, float x, float y, float z)
{
        glUniform3f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y, z);
}

void OpenGL_Uniform4f(RHIShader shader, const char *name, float x, float y, float z, float w)
{
        glUniform4f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y, z, w);
}

void OpenGL_UniformMatrix2fv(RHIShader shader, const char *name, float *matrix)
{
        glUniformMatrix2fv(glGetUniformLocation(CONV_SHADER(shader)->program, name), 1, GL_FALSE, matrix);
}

void OpenGL_UniformMatrix3fv(RHIShader shader, const char *name, float *matrix)
{
        glUniformMatrix3fv(glGetUniformLocation(CONV_SHADER(shader)->program, name), 1, GL_FALSE, matrix);
}

void OpenGL_UniformMatrix4fv(RHIShader shader, const char *name, float *matrix)
{
        glUniformMatrix4fv(glGetUniformLocation(CONV_SHADER(shader)->program, name), 1, GL_FALSE, matrix);
}

void OpenGL_DeleteShader(RHIShader shader)
{
        IShader pShader = CONV_SHADER(shader);
        glDeleteProgram(pShader->program);

        vfree(pShader);
}

void OpenGL_ClearColorBuffer(float r, float g, float b, float a)
{
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
}

RHITexture OpenGL_GenTexture(RHIFormat imageFormat, anciu32 width, anciu32 height, anciuc *pixels)
{
        anciu32 textureId;
        GLint   format;

        format = GL_RGB;

        if (imageFormat == RHI_IMAGE_FORMAT_RGB)
                format = GL_RGB;

        if (imageFormat == RHI_IMAGE_FORMAT_RGBA)
                format = GL_RGBA;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);

        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        RHITextureGL *pTextureGL = vmalloc(sizeof(RHITextureGL));
        pTextureGL->textureId = textureId;
        pTextureGL->width = width;
        pTextureGL->height = height;

        return pTextureGL;
}

void OpenGL_BindTexture(RHITexture texture)
{
        ITexture itexture = CONV_TEX(texture);
        glActiveTexture(GL_TEXTURE0 + _activeTexture);
        glBindTexture(GL_TEXTURE_2D, itexture->textureId);
        _activeTexture++;
}

void OpenGL_DeleteTexture(RHITexture texture)
{
        ITexture itexture = CONV_TEX(texture);
        glDeleteTextures(1, &itexture->textureId);

        vfree(itexture);
}

void RHIAPIFuncLoad()
{
        ANCIRHIGETTIME                          = GLFW_GetTime;
        ANCIRHIVIEWPORT                         = OpenGL_GLViewport;
        ANCIRHISWAPBUFFERS                      = OpenGL_GLSwapBuffers;
        ANCIRHIGENVTXBUFFER                     = OpenGL_GenVtxBuffer;
        ANCIRHIGENIDXBUFFER                     = OpenGL_GenIdxBuffer;
        ANCIRHIDELETEVTXBUFFER                  = OpenGL_DestroyVtxBuffer;
        ANCIRHIDELETEIDXBUFFER                  = OpenGL_DestroyIdxBuffer;
        ANCIRHIBINDVTX                          = OpenGL_BindVtxBuffer;
        ANCIRHIDRAWVTX                          = OpenGL_DrawVtx;
        ANCIRHIDRAWIDX                          = OpenGL_DrawIdx;
        ANCIRHIPOLYGONMODE                      = OpenGL_PolygonMode;
        ANCIRHICREATESHADER                     = OpenGL_CreateShader;
        ANCIRHIBINDSHADER                       = OpenGL_BindShader;
        ANCIRHIUNIFORMINT                       = OpenGL_Uniform1i;
        ANCIRHIUNIFORMFLOAT2                    = OpenGL_Uniform2f;
        ANCIRHIUNIFORMFLOAT3                    = OpenGL_Uniform3f;
        ANCIRHIUNIFORMFLOAT4                    = OpenGL_Uniform4f;
        ANCIRHIUNIFORMMATRIX2FV                 = OpenGL_UniformMatrix2fv;
        ANCIRHIUNIFORMMATRIX3FV                 = OpenGL_UniformMatrix3fv;
        ANCIRHIUNIFORMMATRIX4FV                 = OpenGL_UniformMatrix4fv;
        ANCIRHIDELETESHADER                     = OpenGL_DeleteShader;
        ANCIRHICLEARCOLORBUFFER                 = OpenGL_ClearColorBuffer;
        ANCIRHIGENTEXTURE                       = OpenGL_GenTexture;
        ANCIRHIDELETETEXTURE                    = OpenGL_DeleteTexture;
        ANCIRHIBINDTEXTURE                      = OpenGL_BindTexture;
}

