/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include <RHI/RHI.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

ANCI_RHI_VIEWPORT       ANCIRHIVIEWPORT = nullptr;
ANCI_RHI_SWAP_BUFFERS   ANCIRHISWAPBUFFERS = nullptr;

void OpenGL_GLViewport    (u32 x, u32 y, u32 w, u32 h)  { glViewport((GLint) x, (GLint) y, (GLsizei) w, (GLsizei) h); }
void OpenGL_GLSwapBuffers (ANCI_WINDOW_HANDLE h)        { glfwSwapBuffers((GLFWwindow *) h); }

void RHIApiLoad()
{
        ANCIRHIVIEWPORT         = OpenGL_GLViewport;
        ANCIRHISWAPBUFFERS      = OpenGL_GLSwapBuffers;
}