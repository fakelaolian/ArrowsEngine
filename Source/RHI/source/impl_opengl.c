/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "RHI.h"

#include <stdio.h>

#include "alsl.h"
#include "glfw.h"
#include "verror.h"

ARROWS_RHI_GET_TIME                       ARROWSRHIGETTIME                    = NULL;
ARROWS_RHI_VIEWPORT                       ARROWSRHIVIEWPORT                   = NULL;
ARROWS_RHI_SWAP_BUFFERS                   ARROWSRHISWAPBUFFERS                = NULL;
ARROWS_RHI_GEN_IDXBUFFER                  ARROWSRHICREATEIDXBUFFER            = NULL;
ARROWS_RHI_GEN_VTXBUFFER                  ARROWSRHICREATEVTXBUFFER            = NULL;
ARROWS_RHI_DESTROY_VTX_BUFFER             ARROWSRHIDESTROYVTXBUFFER           = NULL;
ARROWS_RHI_DESTROY_IDX_BUFFER             ARROWSRHIDESTROYIDXBUFFER           = NULL;
ARROWS_RHI_BIND_VTX                       ARROWSRHIBINDVTX                    = NULL;
ARROWS_RHI_DRAW_VTX                       ARROWSRHIDRAWVTX                    = NULL;
ARROWS_RHI_DRAW_IDX                       ARROWSRHIDRAWIDX                    = NULL;
ARROWS_RHI_POLYGON_MODE                   ARROWSRHIPOLYGONMODE                = NULL;
ARROWS_RHI_CREATE_SHADER                  ARROWSRHICREATESHADER               = NULL;
ARROWS_RHI_BIND_SHADER                    ARROWSRHIBINDSHADER                 = NULL;
ARROWS_RHI_UNIFORM_FLOAT1                 ARROWSRHIUNIFORMFLOAT1              = NULL;
ARROWS_RHI_UNIFORM_FLOAT2                 ARROWSRHIUNIFORMFLOAT2              = NULL;
ARROWS_RHI_UNIFORM_INT                    ARROWSRHIUNIFORMINT                 = NULL;
ARROWS_RHI_UNIFORM_FLOAT3                 ARROWSRHIUNIFORMFLOAT3              = NULL;
ARROWS_RHI_UNIFORM_FLOAT3V                ARROWSRHIUNIFORMFLOAT3V             = NULL;
ARROWS_RHI_UNIFORM_FLOAT4                 ARROWSRHIUNIFORMFLOAT4              = NULL;
ARROWS_RHI_UNIFORM_MATRIX2FV              ARROWSRHIUNIFORMMATRIX2FV           = NULL;
ARROWS_RHI_UNIFORM_MATRIX3FV              ARROWSRHIUNIFORMMATRIX3FV           = NULL;
ARROWS_RHI_UNIFORM_MATRIX4FV              ARROWSRHIUNIFORMMATRIX4FV           = NULL;
ARROWS_RHI_DELETE_SHADER                  ARROWSRHIDESTROYSHADER              = NULL;
ARROWS_RHI_CLEAR_COLOR_BUFFER             ARROWSRHICLEARCOLORBUFFER           = NULL;
ARROWS_RHI_GEN_TEXTURE2D                  ARROWSRHICREATETEXTURE2D            = NULL;
ARROWS_RHI_DELETE_TEXTURE                 ARROWSRHIDESTROYTEXTURE             = NULL;
ARROWS_RHI_ENABLE                         ARROWSRHIENABLE                     = NULL;
ARROWS_RHI_GET_TEXTURE_ID                 ARROWSRHIGETTEXTUREID               = NULL;
ARROWS_RHI_BIND_TEXTURE                   ARROWSRHIBINDTEXTURE                = NULL;
ARROWS_RHI_CREATE_TEXTURE_CUBE_MAP        ARROWSRHICREATETEXTURECUBEMAP       = NULL;
ARROWS_RHI_DEPTH_OPTION                   ARROWSRHIDEPTHOPTION                = NULL;
ARROWS_RHI_CREATE_FRAMEBUFFER             ARROWSRHICREATEFRAMEBUFFER          = NULL;
ARROWS_RHI_RECREATE_FRAMEBUFFER           ARROWSRHIRECREATEFRAMEBUFFER        = NULL;
ARROWS_RHI_BIND_FRAMEBUFFER               ARROWSRHIBINDFRAMEBUFFER            = NULL;
ARROWS_RHI_GET_FRAMEBUFFER_TEXTURE        ARROWSRHIGETFRAMEBUFFERTEXTURE      = NULL;
ARROWS_RHI_DELETE_FRAMEBUFFER             ARROWSRHIDELETEFRAMEBUFFER          = NULL;

GLbitfield                              _gl_clear_bits                    = GL_COLOR_BUFFER_BIT;
arrobool                                _gl_depth_test_enable_state       = RHI_FALSE;
arrou32                                 _activeTexture                    = 0;

/** OpenGL的Vertex Buffer实现 */
typedef struct RHIVertexBufferGL {
        arrou32 vao;
        arrou32 vbo;
        arrou32 count;
} RHIVertexBufferGL;
#define IVtxBuffer RHIVertexBufferGL *
#define CONV_VTX(ptr) ((RHIVertexBufferGL *) (ptr))

/** OpenGL的Index Buffer实现 */
typedef struct RHIIndicesBufferGL {
        arrou32 ebo;
        arrou32 count;
} RHIIndicesBufferGL;
#define IIdxBuffer RHIIndicesBufferGL *
#define CONV_IDX(ptr) ((RHIIndicesBufferGL *) (ptr))

/** OpenGL的Texture实现 */
typedef struct RHITextureGL {
        arrou32 textureId;
        arrou32 width;
        arrou32 height;
} RHITextureGL;
#define ITexture RHITextureGL *
#define CONV_TEX(ptr) ((RHITextureGL *) (ptr))

/** OpenGL的Shader实现 */
typedef struct RHIShaderGL {
        arrou32 program;
} RHIShaderGL;
#define IShader RHIShaderGL *
#define CONV_SHADER(ptr) ((RHIShaderGL *) (ptr))

typedef struct RHIFramebufferGL {
        unsigned int framebuffer;
        RHITexture   texture;
} RHIFramebufferGL;
#define IFramebuffer RHIFramebufferGL *
#define CONV_FRAMEBUF(ptr) ((RHIFramebufferGL *) (ptr))

float _glfw_get_time () { return glfwGetTime(); }
void _opengl_viewport (arrou32 x, arrou32 y, arrou32 w, arrou32 h) { glViewport((GLint) x, (GLint) y, (GLsizei) w, (GLsizei) h); }
void _opengl_swap_buffers (RHIWindow h) { glfwSwapBuffers((GLFWwindow *) h); }

void _opengl_create_vtx_buffer(RHIVertexBufferMemLayoutInfo *memLayoutInfo, RHIVertexBuffer *vtxBuffer)
{
        arrou32 vao;
        arrou32 vbo;
        arrou32 i;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, memLayoutInfo->vertexCount * memLayoutInfo->stride, memLayoutInfo->pVertices, GL_STATIC_DRAW);

        for (i = 0; i < memLayoutInfo->bufferLayoutCount; i++) {
                RHIVertexBufferLayout layout = memLayoutInfo->pBufferLayout[i];

                GLenum type = GL_FLOAT;
                switch (layout.format) {
                        case RHI_TYPE_FORMAT_FLOAT: type = GL_FLOAT; break;
                        default: printf("ERROR - 不支持的格式。");
                }

                glEnableVertexAttribArray(layout.location);
                glVertexAttribPointer(layout.location, (int) layout.size, type, GL_FALSE, (int) memLayoutInfo->stride, (void*) (size_t) layout.offset);
        }

        /* 解除绑定 */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        RHIVertexBufferGL *pVtxBuffer = vmalloc(sizeof(RHIVertexBufferGL));
        pVtxBuffer->vao = vao;
        pVtxBuffer->vbo = vbo;
        pVtxBuffer->count = memLayoutInfo->vertexCount / memLayoutInfo->stride;

        *vtxBuffer = pVtxBuffer;
}

void _opengl_create_idx_buffer(arrou32 *indices, arrou32 count, RHIIndicesBuffer *idxBuffer)
{
        unsigned int ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(arrou32), indices, GL_STATIC_DRAW);

        RHIIndicesBufferGL *pIdxBuffer = vmalloc(sizeof(RHIIndicesBufferGL));
        pIdxBuffer->ebo = ebo;
        pIdxBuffer->count = count;

        *idxBuffer = pIdxBuffer;
}

void _opengl_delete_vtx_buffer(RHIVertexBuffer vtxBuffer)
{
        IVtxBuffer buffer = CONV_VTX(vtxBuffer);
        glDeleteVertexArrays(1, &buffer->vao);
        glDeleteBuffers(1, &buffer->vbo);

        vfree(buffer);
}

void _opengl_delete_idx_buffer(RHIIndicesBuffer idxBuffer)
{
        IIdxBuffer buffer = CONV_IDX(idxBuffer);
        glDeleteBuffers(1, &buffer->ebo);

        vfree(buffer);
}

void _opengl_bind_vtx_buffer(RHIVertexBuffer vtxBuffer)
{
        glBindVertexArray(CONV_VTX(vtxBuffer)->vao);
}

void _opengl_draw_vtx(arrou32 size, arrou32 offset)
{
        glDrawArrays(GL_TRIANGLES, size, offset);
        _activeTexture = 0;
}

void _opengl_draw_idx(RHIIndicesBuffer idxBuffer)
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
        arrou32         program;
        arrou32         vertex;
        arrou32         fragment;
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

void _opengl_uniform1f(RHIShader shader, const char *name, float x)
{
        glUniform1f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x);
}

void _opengl_uniform2f(RHIShader shader, const char *name, float x, float y)
{
        glUniform2f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y);
}

void _opengl_uniform3f(RHIShader shader, const char *name, float x, float y, float z)
{
        glUniform3f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y, z);
}

void _opengl_uniform3fv(RHIShader shader, const char *name, float* value)
{
        _opengl_uniform3f(shader, name, value[0], value[1], value[2]);
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
        glClear(_gl_clear_bits);
}

GLint _opengl_get_format(RHIFormat format)
{
        if (format == RHI_IMAGE_FORMAT_RGB)
                return GL_RGB;

        if (format == RHI_IMAGE_FORMAT_RGBA)
                return GL_RGBA;

        if (format == RHI_IMAGE_FORMAT_RED)
                return GL_RED;

        return GL_RGBA;
}

GLint _opengl_get_texture_wrap_value(RHITextureWrapModeBits mode)
{
        switch (mode) {
                case RHI_TEXTURE_WRAP_REPEAT:           return GL_REPEAT;
                case RHI_TEXTURE_WRAP_MIRRORED_REPEAT:  return GL_MIRRORED_REPEAT;
                case RHI_TEXTURE_WRAP_CLAMP_TO_EDGE:    return GL_CLAMP_TO_EDGE;
                case RHI_TEXTURE_WRAP_CLAMP_TO_BORDER:  return GL_CLAMP_TO_BORDER;
        }

        verror("不支持的纹理环绕方式。");
        return 0;
}

GLint _opengl_get_texture_filter_value(RHITextureFilterModeBits mode)
{
        switch (mode) {
                case RHI_TEXTURE_FILTER_NEAREST: return GL_NEAREST;
                case RHI_TEXTURE_FILTER_LINEAR:  return GL_LINEAR;
        }

        verror("不支持的纹理过滤方式。");
        return 0;
}

void _opengl_create_texture2d(RHITexture2DCreateInfo *createInfo, RHITexture *p_texture)
{
        arrou32 textureId;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                _opengl_get_format(createInfo->format),
                createInfo->width,
                createInfo->height,
                0,
                _opengl_get_format(createInfo->format),
                GL_UNSIGNED_BYTE,
                createInfo->pPixels
        );
        glGenerateMipmap(GL_TEXTURE_2D);

        // 为当前绑定的纹理对象设置环绕、过滤方式
        if (createInfo->textureWrapS != RHI_TEXTURE_WRAP_NONE)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _opengl_get_texture_wrap_value(createInfo->textureWrapS));
        if (createInfo->textureWrapT != RHI_TEXTURE_WRAP_NONE)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _opengl_get_texture_wrap_value(createInfo->textureWrapT));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _opengl_get_texture_filter_value(createInfo->textureFilterMin));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _opengl_get_texture_filter_value(createInfo->textureFilterMag));

        RHITextureGL *pTextureGL = vmalloc(sizeof(RHITextureGL));
        pTextureGL->textureId = textureId;
        pTextureGL->width = createInfo->width;
        pTextureGL->height = createInfo->height;

        *p_texture = pTextureGL;
}

void _opengl_delete_texture(RHITexture texture)
{
        ITexture itexture = CONV_TEX(texture);
        glDeleteTextures(1, &itexture->textureId);

        vfree(itexture);
}

void _opengl_enbale(RHIEnableBits enable, arrobool is_enable)
{
        switch (enable) {
                case RHI_DEPTH_TEST: {
                        if (_gl_depth_test_enable_state == is_enable) return;

                        if (is_enable) {
                                glEnable(GL_DEPTH_TEST);
                                _gl_clear_bits |= GL_DEPTH_BUFFER_BIT;
                        } else {
                                glDisable(GL_DEPTH_TEST);
                                _gl_clear_bits ^= GL_DEPTH_BUFFER_BIT;
                        }

                        _gl_depth_test_enable_state = is_enable;
                        return;
                }
        }
}

RHIID _opengl_get_texture_id(RHITexture texture)
{
        return CONV_TEX(texture)->textureId;
}

void _opengl_create_texture_cube_map(RHITextureCubeCreateInfo *createInfo, RHITexture *texture)
{
        arrou32 textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

        for (int i = 0; i < 6; i++) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                             0,
                             _opengl_get_format(createInfo->format[i]),
                             createInfo->width[i],
                             createInfo->height[i],
                             0,
                             _opengl_get_format(createInfo->format[i]),
                             GL_UNSIGNED_BYTE,
                             createInfo->pPixels[i]);
        }

        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, _opengl_get_texture_wrap_value(createInfo->textureWrapS));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, _opengl_get_texture_wrap_value(createInfo->textureWrapT));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, _opengl_get_texture_wrap_value(createInfo->textureWrapR));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, _opengl_get_texture_filter_value(createInfo->textureFilterMin));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, _opengl_get_texture_filter_value(createInfo->textureFilterMag));

        RHITextureGL *pTextureGL = vmalloc(sizeof(RHITextureGL));
        pTextureGL->textureId = textureId;

        *texture = pTextureGL;
}

void _opengl_depth_option(RHIDepthOptionBits bits)
{
        GLenum op;
        switch(bits) {
                case RHI_DEPTH_OPTION_ALWAYS: op = GL_ALWAYS; break;
                case RHI_DEPTH_OPTION_NEVER: op = GL_NEVER; break;
                case RHI_DEPTH_OPTION_EQ: op = GL_EQUAL;break;
                case RHI_DEPTH_OPTION_NE: op = GL_NOTEQUAL; break;
                case RHI_DEPTH_OPTION_LT: op = GL_LESS; break;
                case RHI_DEPTH_OPTION_LE: op = GL_LEQUAL; break;
                case RHI_DEPTH_OPTION_GT: op = GL_GREATER; break;
                case RHI_DEPTH_OPTION_GE: op = GL_GEQUAL; break;
        }

        glDepthFunc(op);
}

void _opengl_bind_texture(RHITextureFormatBits bit, RHITexture texture)
{
        glActiveTexture(GL_TEXTURE0 + _activeTexture);
        if (bit == RHI_TEXTURE_2D)
                glBindTexture(GL_TEXTURE_2D, CONV_TEX(texture)->textureId);
        if (bit == RHI_TEXTURE_CUBE_MAP)
                glBindTexture(GL_TEXTURE_CUBE_MAP, CONV_TEX(texture)->textureId);

        _activeTexture++;
}

arrobool _opengl_create_framebuffer(RHIFramebufferCreateInfo *createFramebuffer, RHIFramebuffer *buffer)
{
        glViewport(0, 0, createFramebuffer->width, createFramebuffer->height);

        unsigned int fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        /* 创建帧缓冲区纹理 */
        RHITexture2DCreateInfo createInfo;
        createInfo.width  = createFramebuffer->width;
        createInfo.height = createFramebuffer->height;
        createInfo.format = RHI_IMAGE_FORMAT_RGBA;
        createInfo.textureWrapS = RHI_TEXTURE_WRAP_CLAMP_TO_EDGE;
        createInfo.textureWrapT = RHI_TEXTURE_WRAP_CLAMP_TO_EDGE;
        createInfo.textureFilterMin = RHI_TEXTURE_FILTER_LINEAR;
        createInfo.textureFilterMag = RHI_TEXTURE_FILTER_LINEAR;
        createInfo.pPixels = NULL;

        RHITexture framebufferTexture;
        _opengl_create_texture2d(&createInfo, &framebufferTexture);

        /* 将纹理绑定到帧缓冲区 */
        glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_2D,
                CONV_TEX(framebufferTexture)->textureId,
                0
        );

        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(
                GL_RENDERBUFFER,
                GL_DEPTH24_STENCIL8,
                createFramebuffer->width,
                createFramebuffer->height
        );
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        /* 检查帧缓冲是否完整 */
        GLenum _checkret = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (_checkret != GL_FRAMEBUFFER_COMPLETE) {
                VERROR("ERROR - 帧缓冲区不完整。");
                return RHI_FALSE;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        RHIFramebufferGL *p_framebuffer = malloc(sizeof(RHIFramebufferGL));
        p_framebuffer->framebuffer = fbo;
        p_framebuffer->texture     = framebufferTexture;
        *buffer = p_framebuffer;

        return RHI_TRUE;
}

void _opengl_delete_framebuffer(RHIFramebuffer framebuffer)
{
        IFramebuffer framebufferGl = CONV_FRAMEBUF(framebuffer);
        glDeleteFramebuffers(1, &framebufferGl->framebuffer);
        _opengl_delete_texture(framebufferGl->texture);
}

void _opengl_recreate_framebuffer(RHIFramebufferCreateInfo *createFramebuffer, RHIFramebuffer *buffer)
{
        _opengl_delete_framebuffer(*buffer);
        _opengl_create_framebuffer(createFramebuffer, buffer);
}

void _opengl_bind_framebuffer(RHIFramebuffer framebuffer)
{
        framebuffer == NULL ? glBindFramebuffer(GL_FRAMEBUFFER, 0) :
        glBindFramebuffer(GL_FRAMEBUFFER, CONV_FRAMEBUF(framebuffer)->framebuffer);
}

RHITexture _opengl_get_framebuffer_texture(RHIFramebuffer framebuffer)
{ return CONV_FRAMEBUF(framebuffer)->texture; }

void OpenGLRHIImpl()
{
        _load_glfw_functions();
        ARROWSRHIGETTIME                          = _glfw_get_time;
        ARROWSRHIVIEWPORT                         = _opengl_viewport;
        ARROWSRHISWAPBUFFERS                      = _opengl_swap_buffers;
        ARROWSRHICREATEVTXBUFFER                  = _opengl_create_vtx_buffer;
        ARROWSRHICREATEIDXBUFFER                  = _opengl_create_idx_buffer;
        ARROWSRHIDESTROYVTXBUFFER                 = _opengl_delete_vtx_buffer;
        ARROWSRHIDESTROYIDXBUFFER                 = _opengl_delete_idx_buffer;
        ARROWSRHIBINDVTX                          = _opengl_bind_vtx_buffer;
        ARROWSRHIDRAWVTX                          = _opengl_draw_vtx;
        ARROWSRHIDRAWIDX                          = _opengl_draw_idx;
        ARROWSRHIPOLYGONMODE                      = _opengl_polygon_mode;
        ARROWSRHICREATESHADER                     = _opengl_create_shader;
        ARROWSRHIBINDSHADER                       = _opengl_bind_shader;
        ARROWSRHIUNIFORMINT                       = _opengl_uniform1i;
        ARROWSRHIUNIFORMFLOAT1                    = _opengl_uniform1f;
        ARROWSRHIUNIFORMFLOAT2                    = _opengl_uniform2f;
        ARROWSRHIUNIFORMFLOAT3                    = _opengl_uniform3f;
        ARROWSRHIUNIFORMFLOAT3V                   = _opengl_uniform3fv;
        ARROWSRHIUNIFORMFLOAT4                    = _opengl_uniform4f;
        ARROWSRHIUNIFORMMATRIX2FV                 = _opengl_uniform_matrix2fv;
        ARROWSRHIUNIFORMMATRIX3FV                 = _opengl_uniform_matrix3fv;
        ARROWSRHIUNIFORMMATRIX4FV                 = _opengl_uniform_matrix4fv;
        ARROWSRHIDESTROYSHADER                    = _opengl_delete_shader;
        ARROWSRHICLEARCOLORBUFFER                 = _opengl_clear_color;
        ARROWSRHICREATETEXTURE2D                  = _opengl_create_texture2d;
        ARROWSRHICREATETEXTURECUBEMAP             = _opengl_create_texture_cube_map;
        ARROWSRHIDESTROYTEXTURE                   = _opengl_delete_texture;
        ARROWSRHIGETTEXTUREID                     = _opengl_get_texture_id;
        ARROWSRHIBINDTEXTURE                      = _opengl_bind_texture;
        ARROWSRHIENABLE                           = _opengl_enbale;
        ARROWSRHIDEPTHOPTION                      = _opengl_depth_option;
        ARROWSRHICREATEFRAMEBUFFER                = _opengl_create_framebuffer;
        ARROWSRHIRECREATEFRAMEBUFFER              = _opengl_recreate_framebuffer;
        ARROWSRHIBINDFRAMEBUFFER                  = _opengl_bind_framebuffer;
        ARROWSRHIGETFRAMEBUFFERTEXTURE            = _opengl_get_framebuffer_texture;
        ARROWSRHIDELETEFRAMEBUFFER                = _opengl_delete_framebuffer;
}

