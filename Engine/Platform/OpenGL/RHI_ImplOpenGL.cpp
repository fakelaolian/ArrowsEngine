/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include <RHI/RHI.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

ANCI_RHI_VIEWPORT       ANCIRHIVIEWPORT             = nullptr;
ANCI_RHI_SWAP_BUFFERS   ANCIRHISWAPBUFFERS          = nullptr;
ANCI_RHI_GEN_IDXBUFFER  ANCIRHIGENIDXBUFFER         = nullptr;
ANCI_RHI_GEN_VTXBUFFER  ANCIRHIGENVTXBUFFER         = nullptr;
ANCI_RHI_DESTROY_VTX_BUFFER ANCIRHIDESTROYVTXBUFFER = nullptr;
ANCI_RHI_DESTROY_IDX_BUFFER ANCIRHIDESTROYIDXBUFFER = nullptr;
ANCI_RHI_BIND_VTX       ANCIRHIBINDVTX              = nullptr;
ANCI_RHI_DRAW_VTX       ANCIRHIDRAWVTX              = nullptr;
ANCI_RHI_DRAW_IDX       ANCIRHIDRAWIDX              = nullptr;
ANCI_RHI_CREATE_SHADER  ANCIRHICreateShader         = nullptr;

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

/** OpenGL的Shader实现 */
struct RHIShader_ImplOpenGL {
        anciu32 shader;
};
#define IShader RHIShader_ImplOpenGL *
#define CONV_SHADER(ptr) ((RHIShader_ImplOpenGL *) (ptr))

void OpenGL_GLViewport    (anciu32 x, anciu32 y, anciu32 w, anciu32 h)
{
        glViewport((GLint) x, (GLint) y, (GLsizei) w, (GLsizei) h);
}

void OpenGL_GLSwapBuffers (ANCI_WINDOW_HANDLE h)
{
        glfwSwapBuffers((GLFWwindow *) h);
}

RHIVtxBuffer OpenGL_GenVtxBuffer(float *vertices, anciu32 count)
{
        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, count, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, count * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        return new RHIVtxBuffer_ImplOpenGL{vao, vbo, count};
}

RHIIdxBuffer OpenGL_GenIdxBuffer(anciu32 *indices, anciu32 count)
{
        unsigned int ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);

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

void OpenGL_DrawVtx(RHIVtxBuffer vtxBuffer)
{
        IVtxBuffer buffer = CONV_VTX(vtxBuffer);
        glBindVertexArray(buffer->vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
}

RHIShader OpenGL_CreateShader(const char* source, RHIEnumCreateShaderMode mode)
{
        anciu32 shader;
        GLenum  glMode;
        int     success;
        char    infoLog[512];

        if (mode == RHI_VERTEX_SHADER) glMode = GL_VERTEX_SHADER;
        else                           glMode = GL_FRAGMENT_SHADER;

        shader = glCreateShader(glMode);

        /* 编译shader源码 */
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        /* 检测shader是否编译成功 */
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                throw std::runtime_error(infoLog);
        }

        return new RHIShader_ImplOpenGL{shader};
}

void RHIApiLoad()
{
        ANCIRHIVIEWPORT         = OpenGL_GLViewport;
        ANCIRHISWAPBUFFERS      = OpenGL_GLSwapBuffers;
        ANCIRHIGENVTXBUFFER     = OpenGL_GenVtxBuffer;
        ANCIRHIGENIDXBUFFER     = OpenGL_GenIdxBuffer;
        ANCIRHIDESTROYVTXBUFFER = OpenGL_DestroyVtxBuffer;
        ANCIRHIDESTROYIDXBUFFER = OpenGL_DestroyIdxBuffer;
        ANCIRHIBINDVTX          = OpenGL_BindVtxBuffer;
        ANCIRHIDRAWVTX          = OpenGL_DrawVtx;
        ANCIRHICreateShader     = OpenGL_CreateShader;
}