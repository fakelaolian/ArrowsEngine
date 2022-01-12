/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "RHI.h"

#include <stdio.h>

#include "alsl.h"
#include "glfw.h"

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

float _glfw_get_time        () { return glfwGetTime(); }
void _opengl_viewport    (anciu32 x, anciu32 y, anciu32 w, anciu32 h) { glViewport((GLint) x, (GLint) y, (GLsizei) w, (GLsizei) h); }
void _opengl_swap_buffers (RHIWindow h) { glfwSwapBuffers((GLFWwindow *) h); }

RHIVtxBuffer _opengl_gen_vtx_buffer(const void *pVertices, RHIVtxBufferCreateInfo *createInfo)
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

                GLenum type = GL_FLOAT;
                switch (layout.format) {
                        case RHI_FLOAT: type = GL_FLOAT; break;
                        default: printf("ERROR - 不支持的格式。");
                }

                glEnableVertexAttribArray(layout.location);
                glVertexAttribPointer(layout.location, (int) layout.size, type, GL_FALSE, (int) createInfo->stride, (void*) (size_t) layout.offset);
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

RHIIdxBuffer _opengl_gen_idx_buffer(anciu32 *indices, anciu32 count)
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

void _opengl_delete_vtx_buffer(RHIVtxBuffer vtxBuffer)
{
        IVtxBuffer buffer = CONV_VTX(vtxBuffer);
        glDeleteVertexArrays(1, &buffer->vao);
        glDeleteBuffers(1, &buffer->vbo);

        vfree(buffer);
}

void _opengl_delete_idx_buffer(RHIIdxBuffer idxBuffer)
{
        IIdxBuffer buffer = CONV_IDX(idxBuffer);
        glDeleteBuffers(1, &buffer->ebo);

        vfree(buffer);
}

void _opengl_bind_vtx_buffer(RHIVtxBuffer vtxBuffer)
{
        glBindVertexArray(CONV_VTX(vtxBuffer)->vao);
}

void _opengl_draw_vtx()
{
        glDrawArrays(GL_TRIANGLES, 0, 3);
        _activeTexture = 0;
}

void _opengl_draw_idx(RHIIdxBuffer idxBuffer)
{
        IIdxBuffer buffer = CONV_IDX(idxBuffer);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->ebo);
        glDrawElements(GL_TRIANGLES, buffer->count, GL_UNSIGNED_INT, 0);
        _activeTexture = 0;
}

void _opengl_polygon_mode(RHIPolygonModeBits mode)
{
        switch (mode) {
                case RHI_POLYGON_MODE_FILL:  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  break;
                case RHI_POLYGON_MODE_LINE:  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  break;
                case RHI_POLYGON_MODE_POINT: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
        }
}

RHIShader _opengl_create_shader(const char* file)
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

void _opengl_bind_shader(RHIShader shader)
{
        glUseProgram(CONV_SHADER(shader)->program);
}

void _opengl_uniform1i(RHIShader shader, const char *name, int value)
{
        glUniform1i(glGetUniformLocation(CONV_SHADER(shader)->program, name), value);
}

void _opengl_uniform2f(RHIShader shader, const char *name, float x, float y)
{
        glUniform2f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y);
}

void _opengl_uniform3f(RHIShader shader, const char *name, float x, float y, float z)
{
        glUniform3f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y, z);
}

void _opengl_uniform4f(RHIShader shader, const char *name, float x, float y, float z, float w)
{
        glUniform4f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y, z, w);
}

void _opengl_uniform_matrix2fv(RHIShader shader, const char *name, float *matrix)
{
        glUniformMatrix2fv(glGetUniformLocation(CONV_SHADER(shader)->program, name), 1, GL_FALSE, matrix);
}

void _opengl_uniform_matrix3fv(RHIShader shader, const char *name, float *matrix)
{
        glUniformMatrix3fv(glGetUniformLocation(CONV_SHADER(shader)->program, name), 1, GL_FALSE, matrix);
}

void _opengl_uniform_matrix4fv(RHIShader shader, const char *name, float *matrix)
{
        glUniformMatrix4fv(glGetUniformLocation(CONV_SHADER(shader)->program, name), 1, GL_FALSE, matrix);
}

void _opengl_delete_shader(RHIShader shader)
{
        IShader pShader = CONV_SHADER(shader);
        glDeleteProgram(pShader->program);

        vfree(pShader);
}

void _opengl_clear_color(float r, float g, float b, float a)
{
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
}

RHITexture _opengl_gen_texture(RHIFormat imageFormat, anciu32 width, anciu32 height, anciuc *pixels)
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

void _opengl_bind_texture(RHITexture texture)
{
        ITexture itexture = CONV_TEX(texture);
        glActiveTexture(GL_TEXTURE0 + _activeTexture);
        glBindTexture(GL_TEXTURE_2D, itexture->textureId);
        _activeTexture++;
}

void _opengl_delete_texture(RHITexture texture)
{
        ITexture itexture = CONV_TEX(texture);
        glDeleteTextures(1, &itexture->textureId);

        vfree(itexture);
}

void OpenGLRHIImpl()
{
        _load_glfw_functions();
        ANCIRHIGETTIME                          = _glfw_get_time;
        ANCIRHIVIEWPORT                         = _opengl_viewport;
        ANCIRHISWAPBUFFERS                      = _opengl_swap_buffers;
        ANCIRHIGENVTXBUFFER                     = _opengl_gen_vtx_buffer;
        ANCIRHIGENIDXBUFFER                     = _opengl_gen_idx_buffer;
        ANCIRHIDELETEVTXBUFFER                  = _opengl_delete_vtx_buffer;
        ANCIRHIDELETEIDXBUFFER                  = _opengl_delete_idx_buffer;
        ANCIRHIBINDVTX                          = _opengl_bind_vtx_buffer;
        ANCIRHIDRAWVTX                          = _opengl_draw_vtx;
        ANCIRHIDRAWIDX                          = _opengl_draw_idx;
        ANCIRHIPOLYGONMODE                      = _opengl_polygon_mode;
        ANCIRHICREATESHADER                     = _opengl_create_shader;
        ANCIRHIBINDSHADER                       = _opengl_bind_shader;
        ANCIRHIUNIFORMINT                       = _opengl_uniform1i;
        ANCIRHIUNIFORMFLOAT2                    = _opengl_uniform2f;
        ANCIRHIUNIFORMFLOAT3                    = _opengl_uniform3f;
        ANCIRHIUNIFORMFLOAT4                    = _opengl_uniform4f;
        ANCIRHIUNIFORMMATRIX2FV                 = _opengl_uniform_matrix2fv;
        ANCIRHIUNIFORMMATRIX3FV                 = _opengl_uniform_matrix3fv;
        ANCIRHIUNIFORMMATRIX4FV                 = _opengl_uniform_matrix4fv;
        ANCIRHIDELETESHADER                     = _opengl_delete_shader;
        ANCIRHICLEARCOLORBUFFER                 = _opengl_clear_color;
        ANCIRHIGENTEXTURE                       = _opengl_gen_texture;
        ANCIRHIDELETETEXTURE                    = _opengl_delete_texture;
        ANCIRHIBINDTEXTURE                      = _opengl_bind_texture;
}

