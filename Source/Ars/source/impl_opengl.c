/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include "Ars.h"

#include <stdio.h>

#include "alsl.h"
#include "glfw.h"
#include "verror.h"

RHI_ARS_GET_TIME                       RHIARSGETTIME                    = NULL;
RHI_ARS_VIEWPORT                       RHIARSVIEWPORT                   = NULL;
RHI_ARS_SWAP_BUFFERS                   RHIARSSWAPBUFFERS                = NULL;
RHI_ARS_GEN_IDXBUFFER                  RHIARSCREATEIDXBUFFER            = NULL;
RHI_ARS_GEN_VTXBUFFER                  RHIARSCREATEVTXBUFFER            = NULL;
RHI_ARS_DESTROY_VTX_BUFFER             RHIARSDESTROYVTXBUFFER           = NULL;
RHI_ARS_DESTROY_IDX_BUFFER             RHIARSDESTROYIDXBUFFER           = NULL;
RHI_ARS_BIND_VTX                       RHIARSBINDVTX                    = NULL;
RHI_ARS_DRAW_VTX                       RHIARSDRAWVTX                    = NULL;
RHI_ARS_DRAW_IDX                       RHIARSDRAWIDX                    = NULL;
RHI_ARS_POLYGON_MODE                   RHIARSPOLYGONMODE                = NULL;
RHI_ARS_CREATE_SHADER                  RHIARSCREATESHADER               = NULL;
RHI_ARS_BIND_SHADER                    RHIARSBINDSHADER                 = NULL;
RHI_ARS_UNIFORM_FLOAT1                 RHIARSUNIFORMFLOAT1              = NULL;
RHI_ARS_UNIFORM_FLOAT2                 RHIARSUNIFORMFLOAT2              = NULL;
RHI_ARS_UNIFORM_INT                    RHIARSUNIFORMINT                 = NULL;
RHI_ARS_UNIFORM_FLOAT3                 RHIARSUNIFORMFLOAT3              = NULL;
RHI_ARS_UNIFORM_FLOAT3V                RHIARSUNIFORMFLOAT3V             = NULL;
RHI_ARS_UNIFORM_FLOAT4                 RHIARSUNIFORMFLOAT4              = NULL;
RHI_ARS_UNIFORM_MATRIX2FV              RHIARSUNIFORMMATRIX2FV           = NULL;
RHI_ARS_UNIFORM_MATRIX3FV              RHIARSUNIFORMMATRIX3FV           = NULL;
RHI_ARS_UNIFORM_MATRIX4FV              RHIARSUNIFORMMATRIX4FV           = NULL;
RHI_ARS_DELETE_SHADER                  RHIARSDESTROYSHADER              = NULL;
RHI_ARS_CLEAR_COLOR_BUFFER             RHIARSCLEARCOLORBUFFER           = NULL;
RHI_ARS_GEN_TEXTURE2D                  RHIARSCREATETEXTURE2D            = NULL;
RHI_ARS_DELETE_TEXTURE                 RHIARSDESTROYTEXTURE             = NULL;
RHI_ARS_ENABLE                         RHIARSENABLE                     = NULL;
RHI_ARS_GET_TEXTURE_ID                 RHIARSGETTEXTUREID               = NULL;
RHI_ARS_BIND_TEXTURE                   RHIARSBINDTEXTURE                = NULL;
RHI_ARS_RESET_ACTIVE_TEXTURE           RHIARSRESETACTIVETEXTURE         = NULL;
RHI_ARS_CREATE_TEXTURE_CUBE_MAP        RHIARSCREATETEXTURECUBEMAP       = NULL;
RHI_ARS_DEPTH_OPTION                   RHIARSDEPTHOPTION                = NULL;
RHI_ARS_CREATE_FRAMEBUFFER             RHIARSCREATEFRAMEBUFFER          = NULL;
RHI_ARS_RECREATE_FRAMEBUFFER           RHIARSRECREATEFRAMEBUFFER        = NULL;
RHI_ARS_BIND_FRAMEBUFFER               RHIARSBINDFRAMEBUFFER            = NULL;
RHI_ARS_GET_FRAMEBUFFER_TEXTURE        RHIARSGETFRAMEBUFFERTEXTURE      = NULL;
RHI_ARS_DELETE_FRAMEBUFFER             RHIARSDELETEFRAMEBUFFER          = NULL;

GLbitfield                             _gl_clear_bits                    = GL_COLOR_BUFFER_BIT;
arsbool                                _gl_depth_test_enable_state       = ARS_FALSE;
arsu32                                 _activeTexture                    = 0;

/** OpenGL???Vertex Buffer?????? */
typedef struct ArsVertexBufferGL {
        arsu32 vao;
        arsu32 vbo;
        arsu32 count;
} ArsVertexBufferGL;
#define IVtxBuffer ArsVertexBufferGL *
#define CONV_VTX(ptr) ((ArsVertexBufferGL *) (ptr))

/** OpenGL???Index Buffer?????? */
typedef struct ArsIndicesBufferGL {
        arsu32 ebo;
        arsu32 count;
} ArsIndicesBufferGL;
#define IIdxBuffer ArsIndicesBufferGL *
#define CONV_IDX(ptr) ((ArsIndicesBufferGL *) (ptr))

/** OpenGL???Texture?????? */
typedef struct ArsTextureGL {
        arsu32 textureId;
        arsu32 width;
        arsu32 height;
} ArsTextureGL;
#define ITexture ArsTextureGL *
#define CONV_TEX(ptr) ((ArsTextureGL *) (ptr))

/** OpenGL???Shader?????? */
typedef struct ArsShaderGL {
        arsu32 program;
} ArsShaderGL;
#define IShader ArsShaderGL *
#define CONV_SHADER(ptr) ((ArsShaderGL *) (ptr))

typedef struct ArsFramebufferGL {
        unsigned int framebuffer;
        ArsTexture   texture;
} ArsFramebufferGL;
#define IFramebuffer ArsFramebufferGL *
#define CONV_FRAMEBUF(ptr) ((ArsFramebufferGL *) (ptr))

float _glfw_get_time () { return glfwGetTime(); }
void _opengl_viewport (arsu32 x, arsu32 y, arsu32 w, arsu32 h) { glViewport((GLint) x, (GLint) y, (GLsizei) w, (GLsizei) h); }
void _opengl_swap_buffers (ArsWindow h) { glfwSwapBuffers((GLFWwindow *) h); }

void _opengl_create_vtx_buffer(ArsVertexBufferMemLayoutInfo *memLayoutInfo, ArsVertexBuffer *vtxBuffer)
{
        arsu32 vao;
        arsu32 vbo;
        arsu32 i;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, memLayoutInfo->vertexCount * memLayoutInfo->stride, memLayoutInfo->pVertices, GL_STATIC_DRAW);

        for (i = 0; i < memLayoutInfo->bufferLayoutCount; i++) {
                ArsVertexBufferLayout layout = memLayoutInfo->pBufferLayout[i];

                GLenum type = GL_FLOAT;
                switch (layout.format) {
                        case ARS_TYPE_FORMAT_FLOAT: type = GL_FLOAT; break;
                        default: printf("ERROR - ?????????????????????");
                }

                glEnableVertexAttribArray(layout.location);
                glVertexAttribPointer(layout.location, (int) layout.size, type, GL_FALSE, (int) memLayoutInfo->stride, (void*) (size_t) layout.offset);
        }

        /* ???????????? */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        ArsVertexBufferGL *pVtxBuffer = vmalloc(sizeof(ArsVertexBufferGL));
        pVtxBuffer->vao = vao;
        pVtxBuffer->vbo = vbo;
        pVtxBuffer->count = memLayoutInfo->vertexCount / memLayoutInfo->stride;

        *vtxBuffer = pVtxBuffer;
}

void _opengl_create_idx_buffer(arsu32 *indices, arsu32 count, ArsIndicesBuffer *idxBuffer)
{
        unsigned int ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(arsu32), indices, GL_STATIC_DRAW);

        ArsIndicesBufferGL *pIdxBuffer = vmalloc(sizeof(ArsIndicesBufferGL));
        pIdxBuffer->ebo = ebo;
        pIdxBuffer->count = count;

        *idxBuffer = pIdxBuffer;
}

void _opengl_delete_vtx_buffer(ArsVertexBuffer vtxBuffer)
{
        IVtxBuffer buffer = CONV_VTX(vtxBuffer);
        glDeleteVertexArrays(1, &buffer->vao);
        glDeleteBuffers(1, &buffer->vbo);

        vfree(buffer);
}

void _opengl_delete_idx_buffer(ArsIndicesBuffer idxBuffer)
{
        IIdxBuffer buffer = CONV_IDX(idxBuffer);
        glDeleteBuffers(1, &buffer->ebo);

        vfree(buffer);
}

void _opengl_bind_vtx_buffer(ArsVertexBuffer vtxBuffer)
{
        glBindVertexArray(CONV_VTX(vtxBuffer)->vao);
}

void _opengl_draw_vtx(arsu32 size, arsu32 offset)
{
        glDrawArrays(GL_TRIANGLES, size, offset);
        _activeTexture = 0;
}

void _opengl_draw_idx(ArsIndicesBuffer idxBuffer)
{
        IIdxBuffer buffer = CONV_IDX(idxBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->ebo);
        glDrawElements(GL_TRIANGLES, buffer->count, GL_UNSIGNED_INT, 0);
        _activeTexture = 0;
}

void _opengl_polygon_mode(ArsPolygonModeBits mode)
{
        switch (mode) {
                case ARS_POLYGON_MODE_FILL:  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  break;
                case ARS_POLYGON_MODE_LINE:  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  break;
                case ARS_POLYGON_MODE_POINT: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
        }
}

ArsShader _opengl_create_shader(const char* file)
{
        arsu32         program;
        arsu32         vertex;
        arsu32         fragment;
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
                printf("ERROR - ??????Shader????????? %s\n", infoLog);
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &source.frag, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(fragment, 512, NULL, infoLog);
                printf("ERROR - ??????Shader????????? %s\n", infoLog);
        }

        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success) {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                printf("ERROR - ??????Shader????????? %s\n", infoLog);
        }

        /* ??????shader???????????? */
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        free_shader_source(&source);

        ArsShaderGL *pShaderGL = vmalloc(sizeof(ArsShaderGL));
        pShaderGL->program = program;

        return pShaderGL;
}

void _opengl_bind_shader(ArsShader shader)
{
        glUseProgram(CONV_SHADER(shader)->program);
}

void _opengl_uniform1i(ArsShader shader, const char *name, int value)
{
        glUniform1i(glGetUniformLocation(CONV_SHADER(shader)->program, name), value);
}

void _opengl_uniform1f(ArsShader shader, const char *name, float x)
{
        glUniform1f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x);
}

void _opengl_uniform2f(ArsShader shader, const char *name, float x, float y)
{
        glUniform2f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y);
}

void _opengl_uniform3f(ArsShader shader, const char *name, float x, float y, float z)
{
        glUniform3f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y, z);
}

void _opengl_uniform3fv(ArsShader shader, const char *name, float* value)
{
        _opengl_uniform3f(shader, name, value[0], value[1], value[2]);
}

void _opengl_uniform4f(ArsShader shader, const char *name, float x, float y, float z, float w)
{
        glUniform4f(glGetUniformLocation(CONV_SHADER(shader)->program, name), x, y, z, w);
}

void _opengl_uniform_matrix2fv(ArsShader shader, const char *name, float *matrix)
{
        glUniformMatrix2fv(glGetUniformLocation(CONV_SHADER(shader)->program, name), 1, GL_FALSE, matrix);
}

void _opengl_uniform_matrix3fv(ArsShader shader, const char *name, float *matrix)
{
        glUniformMatrix3fv(glGetUniformLocation(CONV_SHADER(shader)->program, name), 1, GL_FALSE, matrix);
}

void _opengl_uniform_matrix4fv(ArsShader shader, const char *name, float *matrix)
{
        glUniformMatrix4fv(glGetUniformLocation(CONV_SHADER(shader)->program, name), 1, GL_FALSE, matrix);
}

void _opengl_delete_shader(ArsShader shader)
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

GLint _opengl_get_format(ArsFormat format)
{
        if (format == ARS_IMAGE_FORMAT_RGB)
                return GL_RGB;

        if (format == ARS_IMAGE_FORMAT_RGBA)
                return GL_RGBA;

        if (format == ARS_IMAGE_FORMAT_ALPHA)
                return GL_ALPHA;

        if (format == ARS_IMAGE_FORMAT_SRGB)
                return GL_SRGB;

        if (format == ARS_IMAGE_FORMAT_SRGB8)
                return GL_SRGB8;

        if (format == ARS_IMAGE_FORMAT_RED)
                return GL_RED;

        return GL_RGBA;
}

GLint _opengl_get_texture_wrap_value(ArsTextureWrapModeBits mode)
{
        switch (mode) {
                case ARS_TEXTURE_WRAP_REPEAT:           return GL_REPEAT;
                case ARS_TEXTURE_WRAP_MIRRORED_REPEAT:  return GL_MIRRORED_REPEAT;
                case ARS_TEXTURE_WRAP_CLAMP_TO_EDGE:    return GL_CLAMP_TO_EDGE;
                case ARS_TEXTURE_WRAP_CLAMP_TO_BORDER:  return GL_CLAMP_TO_BORDER;
        }

        verror("?????????????????????????????????");
        return 0;
}

GLint _opengl_get_texture_filter_value(ArsTextureFilterModeBits mode)
{
        switch (mode) {
                case ARS_TEXTURE_FILTER_NEAREST: return GL_NEAREST;
                case ARS_TEXTURE_FILTER_LINEAR:  return GL_LINEAR;
                case ARS_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
        }

        verror("?????????????????????????????????");
        return 0;
}

void _opengl_create_texture2d(ArsTexture2DCreateInfo *createInfo, ArsTexture *p_texture)
{
        arsu32 textureId;

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

        // ?????????????????????????????????????????????????????????
        if (createInfo->textureWrapS != ARS_TEXTURE_WRAP_NONE)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _opengl_get_texture_wrap_value(createInfo->textureWrapS));
        if (createInfo->textureWrapT != ARS_TEXTURE_WRAP_NONE)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _opengl_get_texture_wrap_value(createInfo->textureWrapT));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _opengl_get_texture_filter_value(createInfo->textureFilterMin));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _opengl_get_texture_filter_value(createInfo->textureFilterMag));

        ArsTextureGL *pTextureGL = vmalloc(sizeof(ArsTextureGL));
        pTextureGL->textureId = textureId;
        pTextureGL->width = createInfo->width;
        pTextureGL->height = createInfo->height;

        *p_texture = pTextureGL;
}

void _opengl_delete_texture(ArsTexture texture)
{
        ITexture itexture = CONV_TEX(texture);
        glDeleteTextures(1, &itexture->textureId);

        vfree(itexture);
}

void _opengl_enbale(ArsEnableBits enable, arsbool is_enable)
{
        switch (enable) {
                case ARS_DEPTH_TEST: {
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

ArsID _opengl_get_texture_id(ArsTexture texture)
{
        return CONV_TEX(texture)->textureId;
}

void _opengl_create_texture_cube_map(ArsTextureCubeCreateInfo *createInfo, ArsTexture *texture)
{
        arsu32 textureId;
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

        // ?????????????????????????????????????????????????????????
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, _opengl_get_texture_wrap_value(createInfo->textureWrapS));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, _opengl_get_texture_wrap_value(createInfo->textureWrapT));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, _opengl_get_texture_wrap_value(createInfo->textureWrapR));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, _opengl_get_texture_filter_value(createInfo->textureFilterMin));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, _opengl_get_texture_filter_value(createInfo->textureFilterMag));

        ArsTextureGL *pTextureGL = vmalloc(sizeof(ArsTextureGL));
        pTextureGL->textureId = textureId;

        *texture = pTextureGL;
}

void _opengl_depth_option(ArsDepthOptionBits bits)
{
        GLenum op;
        switch(bits) {
                case ARS_DEPTH_OPTION_ALWAYS: op = GL_ALWAYS; break;
                case ARS_DEPTH_OPTION_NEVER: op = GL_NEVER; break;
                case ARS_DEPTH_OPTION_EQ: op = GL_EQUAL;break;
                case ARS_DEPTH_OPTION_NE: op = GL_NOTEQUAL; break;
                case ARS_DEPTH_OPTION_LT: op = GL_LESS; break;
                case ARS_DEPTH_OPTION_LE: op = GL_LEQUAL; break;
                case ARS_DEPTH_OPTION_GT: op = GL_GREATER; break;
                case ARS_DEPTH_OPTION_GE: op = GL_GEQUAL; break;
        }

        glDepthFunc(op);
}

void _opengl_bind_texture(ArsTextureFormatBits bit, ArsTexture texture)
{
        glActiveTexture(GL_TEXTURE0 + _activeTexture);
        if (bit == ARS_TEXTURE_2D)
                glBindTexture(GL_TEXTURE_2D, CONV_TEX(texture)->textureId);
        else if (bit == ARS_TEXTURE_CUBE_MAP)
                glBindTexture(GL_TEXTURE_CUBE_MAP, CONV_TEX(texture)->textureId);

        _activeTexture++;
}

void _opengl_reset_active_texture()
{
        glActiveTexture(GL_TEXTURE0);
}

arsbool _opengl_create_framebuffer(ArsFramebufferCreateInfo *createFramebuffer, ArsFramebuffer *buffer)
{
        glViewport(0, 0, createFramebuffer->width, createFramebuffer->height);

        unsigned int fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        /* ???????????????????????? */
        ArsTexture2DCreateInfo createInfo;
        createInfo.width  = createFramebuffer->width;
        createInfo.height = createFramebuffer->height;
        createInfo.format = ARS_IMAGE_FORMAT_RGBA;
        createInfo.textureWrapS = ARS_TEXTURE_WRAP_CLAMP_TO_EDGE;
        createInfo.textureWrapT = ARS_TEXTURE_WRAP_CLAMP_TO_EDGE;
        createInfo.textureFilterMin = ARS_TEXTURE_FILTER_LINEAR;
        createInfo.textureFilterMag = ARS_TEXTURE_FILTER_LINEAR;
        createInfo.pPixels = NULL;

        ArsTexture framebufferTexture;
        _opengl_create_texture2d(&createInfo, &framebufferTexture);

        /* ?????????????????????????????? */
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

        /* ??????????????????????????? */
        GLenum _checkret = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (_checkret != GL_FRAMEBUFFER_COMPLETE) {
                VERROR("ERROR - ????????????????????????");
                return ARS_FALSE;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ArsFramebufferGL *p_framebuffer = malloc(sizeof(ArsFramebufferGL));
        p_framebuffer->framebuffer = fbo;
        p_framebuffer->texture     = framebufferTexture;
        *buffer = p_framebuffer;

        return ARS_TRUE;
}

void _opengl_delete_framebuffer(ArsFramebuffer framebuffer)
{
        IFramebuffer framebufferGl = CONV_FRAMEBUF(framebuffer);
        glDeleteFramebuffers(1, &framebufferGl->framebuffer);
        _opengl_delete_texture(framebufferGl->texture);
}

void _opengl_recreate_framebuffer(ArsFramebufferCreateInfo *createFramebuffer, ArsFramebuffer *buffer)
{
        _opengl_delete_framebuffer(*buffer);
        _opengl_create_framebuffer(createFramebuffer, buffer);
}

void _opengl_bind_framebuffer(ArsFramebuffer framebuffer)
{
        framebuffer == NULL ? glBindFramebuffer(GL_FRAMEBUFFER, 0) :
        glBindFramebuffer(GL_FRAMEBUFFER, CONV_FRAMEBUF(framebuffer)->framebuffer);
}

ArsTexture _opengl_get_framebuffer_texture(ArsFramebuffer framebuffer)
{ return CONV_FRAMEBUF(framebuffer)->texture; }

void OpenGLArsImpl()
{
        _load_glfw_functions();
        RHIARSGETTIME                          = _glfw_get_time;
        RHIARSVIEWPORT                         = _opengl_viewport;
        RHIARSSWAPBUFFERS                      = _opengl_swap_buffers;
        RHIARSCREATEVTXBUFFER                  = _opengl_create_vtx_buffer;
        RHIARSCREATEIDXBUFFER                  = _opengl_create_idx_buffer;
        RHIARSDESTROYVTXBUFFER                 = _opengl_delete_vtx_buffer;
        RHIARSDESTROYIDXBUFFER                 = _opengl_delete_idx_buffer;
        RHIARSBINDVTX                          = _opengl_bind_vtx_buffer;
        RHIARSDRAWVTX                          = _opengl_draw_vtx;
        RHIARSDRAWIDX                          = _opengl_draw_idx;
        RHIARSPOLYGONMODE                      = _opengl_polygon_mode;
        RHIARSCREATESHADER                     = _opengl_create_shader;
        RHIARSBINDSHADER                       = _opengl_bind_shader;
        RHIARSUNIFORMINT                       = _opengl_uniform1i;
        RHIARSUNIFORMFLOAT1                    = _opengl_uniform1f;
        RHIARSUNIFORMFLOAT2                    = _opengl_uniform2f;
        RHIARSUNIFORMFLOAT3                    = _opengl_uniform3f;
        RHIARSUNIFORMFLOAT3V                   = _opengl_uniform3fv;
        RHIARSUNIFORMFLOAT4                    = _opengl_uniform4f;
        RHIARSUNIFORMMATRIX2FV                 = _opengl_uniform_matrix2fv;
        RHIARSUNIFORMMATRIX3FV                 = _opengl_uniform_matrix3fv;
        RHIARSUNIFORMMATRIX4FV                 = _opengl_uniform_matrix4fv;
        RHIARSDESTROYSHADER                    = _opengl_delete_shader;
        RHIARSCLEARCOLORBUFFER                 = _opengl_clear_color;
        RHIARSCREATETEXTURE2D                  = _opengl_create_texture2d;
        RHIARSCREATETEXTURECUBEMAP             = _opengl_create_texture_cube_map;
        RHIARSDESTROYTEXTURE                   = _opengl_delete_texture;
        RHIARSGETTEXTUREID                     = _opengl_get_texture_id;
        RHIARSBINDTEXTURE                      = _opengl_bind_texture;
        RHIARSRESETACTIVETEXTURE               = _opengl_reset_active_texture;
        RHIARSENABLE                           = _opengl_enbale;
        RHIARSDEPTHOPTION                      = _opengl_depth_option;
        RHIARSCREATEFRAMEBUFFER                = _opengl_create_framebuffer;
        RHIARSRECREATEFRAMEBUFFER              = _opengl_recreate_framebuffer;
        RHIARSBINDFRAMEBUFFER                  = _opengl_bind_framebuffer;
        RHIARSGETFRAMEBUFFERTEXTURE            = _opengl_get_framebuffer_texture;
        RHIARSDELETEFRAMEBUFFER                = _opengl_delete_framebuffer;
}

