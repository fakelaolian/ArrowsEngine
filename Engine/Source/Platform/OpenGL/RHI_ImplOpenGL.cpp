/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include <RHI/RHI.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLShader.h"

ANCI_RHI_GET_TIME                       ANCIRHIGETTIME              = nullptr;
ANCI_RHI_VIEWPORT                       ANCIRHIVIEWPORT             = nullptr;
ANCI_RHI_SWAP_BUFFERS                   ANCIRHISWAPBUFFERS          = nullptr;
ANCI_RHI_GEN_IDXBUFFER                  ANCIRHIGENIDXBUFFER         = nullptr;
ANCI_RHI_GEN_VTXBUFFER                  ANCIRHIGENVTXBUFFER         = nullptr;
ANCI_RHI_DESTROY_VTX_BUFFER             ANCIRHIDELETEVTXBUFFER      = nullptr;
ANCI_RHI_DESTROY_IDX_BUFFER             ANCIRHIDELETEIDXBUFFER      = nullptr;
ANCI_RHI_BIND_VTX                       ANCIRHIBINDVTX              = nullptr;
ANCI_RHI_DRAW_VTX                       ANCIRHIDRAWVTX              = nullptr;
ANCI_RHI_DRAW_IDX                       ANCIRHIDRAWIDX              = nullptr;
ANCI_RHI_POLYGON_MODE                   ANCIRHIPOLYGONMODE          = nullptr;
ANCI_RHI_CREATE_SHADER                  ANCIRHICREATESHADER         = nullptr;
ANCI_RHI_DELETE_SHADER                  ANCIRHIDELETESHADER         = nullptr;
ANCI_RHI_CLEAR_COLOR_BUFFER             ANCIRHICLEARCOLORBUFFER     = nullptr;
ANCI_RHI_GEN_TEXTURE                    ANCIRHIGENTEXTURE           = nullptr;
ANCI_RHI_DELETE_TEXTURE                 ANCIRHIDELETETEXTURE        = nullptr;
ANCI_RHI_BIND_TEXTURE                   ANCIRHIBINDTEXTURE          = nullptr;

anciu32 _activeTexture                                              = 0;

/** OpenGL的Vertex Buffer实现 */
struct RHIVtxBuffer_ImplOpenGL {
        anciu32 vao;
        anciu32 vbo;
        anciu32 count;
};
#define IVtxBuffer RHIVtxBuffer_ImplOpenGL *
#define CONV_VTX(ptr) ((RHIVtxBuffer_ImplOpenGL *) (ptr))

/** OpenGL的Index Buffer实现 */
struct RHIIdxBuffer_ImplOpenGL {
        anciu32 ebo;
        anciu32 count;
};
#define IIdxBuffer RHIIdxBuffer_ImplOpenGL *
#define CONV_IDX(ptr) ((RHIIdxBuffer_ImplOpenGL *) (ptr))

/** OpenGL的Texture实现 */
struct RHITexture_ImplOpenGL {
        anciu32 textureId;
        anciu32 width;
        anciu32 height;
};
#define ITexture RHITexture_ImplOpenGL *
#define CONV_TEX(ptr) ((RHITexture_ImplOpenGL *) (ptr))

float GLFW_GetTime        () { return glfwGetTime(); }
void OpenGL_GLViewport    (anciu32 x, anciu32 y, anciu32 w, anciu32 h) { glViewport((GLint) x, (GLint) y, (GLsizei) w, (GLsizei) h); }
void OpenGL_GLSwapBuffers (ANCI_WINDOW_HANDLE h) { glfwSwapBuffers((GLFWwindow *) h); }

RHIVtxBuffer OpenGL_GenVtxBuffer(RHIVtxArray *vertices, anciu32 count)
{
        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(RHIVtxArray), vertices, GL_STATIC_DRAW);

        /* 绑定顶点数据对应的布局 */
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(RHIVtxArray), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(RHIVtxArray), (void *) offsetof(RHIVtxArray, color));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(RHIVtxArray), (void *) offsetof(RHIVtxArray, uv));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(RHIVtxArray), (void *) offsetof(RHIVtxArray, normal));

        /* 解除绑定 */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return new RHIVtxBuffer_ImplOpenGL{vao, vbo, count};
}

RHIIdxBuffer OpenGL_GenIdxBuffer(anciu32 *indices, anciu32 count)
{
        unsigned int ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(anciu32), indices, GL_STATIC_DRAW);

        return new RHIIdxBuffer_ImplOpenGL{ebo, count};
}

void OpenGL_DestroyVtxBuffer(RHIVtxBuffer vtxBuffer)
{
        IVtxBuffer buffer = CONV_VTX(vtxBuffer);
        glDeleteVertexArrays(1, &buffer->vao);
        glDeleteBuffers(1, &buffer->vbo);
        delete buffer;
}

void OpenGL_DestroyIdxBuffer(RHIIdxBuffer idxBuffer)
{
        IIdxBuffer buffer = CONV_IDX(idxBuffer);
        glDeleteBuffers(1, &buffer->ebo);
        delete buffer;
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

void OpenGL_PolygonMode(RHIEnumPolygonMode mode)
{
        switch (mode) {
                case RHI_POLYGON_MODE_FILL:  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  break;
                case RHI_POLYGON_MODE_LINE:  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  break;
                case RHI_POLYGON_MODE_POINT: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
        }
}

RHIShader OpenGL_CreateShader(const char* file)
{
        return new OpenGLShader(file);
}

void OpenGL_DeleteShader(RHIShader shader)
{
        delete shader;
}

void OpenGL_ClearColorBuffer(ancivec4 color)
{
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
}

RHITexture OpenGL_GenTexture(RHIEnumImageFormat imageFormat, anciu32 width, anciu32 height, anciuc *pixels)
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

        return new RHITexture_ImplOpenGL{textureId, width, height};
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

       delete itexture;
}

void RHIApiLoad()
{
        ANCIRHIGETTIME          = GLFW_GetTime;
        ANCIRHIVIEWPORT         = OpenGL_GLViewport;
        ANCIRHISWAPBUFFERS      = OpenGL_GLSwapBuffers;
        ANCIRHIGENVTXBUFFER     = OpenGL_GenVtxBuffer;
        ANCIRHIGENIDXBUFFER     = OpenGL_GenIdxBuffer;
        ANCIRHIDELETEVTXBUFFER  = OpenGL_DestroyVtxBuffer;
        ANCIRHIDELETEIDXBUFFER  = OpenGL_DestroyIdxBuffer;
        ANCIRHIBINDVTX          = OpenGL_BindVtxBuffer;
        ANCIRHIDRAWVTX          = OpenGL_DrawVtx;
        ANCIRHIDRAWIDX          = OpenGL_DrawIdx;
        ANCIRHIPOLYGONMODE      = OpenGL_PolygonMode;
        ANCIRHICREATESHADER     = OpenGL_CreateShader;
        ANCIRHIDELETESHADER     = OpenGL_DeleteShader;
        ANCIRHICLEARCOLORBUFFER = OpenGL_ClearColorBuffer;
        ANCIRHIGENTEXTURE       = OpenGL_GenTexture;
        ANCIRHIDELETETEXTURE    = OpenGL_DeleteTexture;
        ANCIRHIBINDTEXTURE      = OpenGL_BindTexture;
}