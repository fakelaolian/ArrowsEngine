/* AUTHOR: 2BKBD, DATE: 2022/1/6 */
#include <RHI/RHI.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

ANCI_RHI_VIEWPORT       ANCIRHIVIEWPORT = nullptr;
ANCI_RHI_SWAP_BUFFERS   ANCIRHISWAPBUFFERS = nullptr;

void OpenGL_GLViewport    (anciu32 x, anciu32 y, anciu32 w, anciu32 h)  { glViewport((GLint) x, (GLint) y, (GLsizei) w, (GLsizei) h); }
void OpenGL_GLSwapBuffers (ANCI_WINDOW_HANDLE h)                        { glfwSwapBuffers((GLFWwindow *) h); }

void AnciLoadRHI()
{
        ANCIRHIVIEWPORT         = OpenGL_GLViewport;
        ANCIRHISWAPBUFFERS      = OpenGL_GLSwapBuffers;
}