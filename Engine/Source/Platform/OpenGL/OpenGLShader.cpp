/* AUTHOR: 2BKBD, DATE: 2022/1/10 */
#include "OpenGLShader.h"
#include "Alsl/Alsl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void CheckCompileSuccessful(anciu32 shaderId)
{
        int  success;
        char compileInfoLog[512];

        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success) {
                glGetShaderInfoLog(shaderId, 512, NULL, compileInfoLog);
                String error = "Shader编译失败：";
                error += compileInfoLog;
                throw std::runtime_error(error.c_str());
        }
}

static void CheckLinkSuccessful(anciu32 programId)
{
        int  success;
        char compileInfoLog[512];

        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success) {
                glGetProgramInfoLog(programId, 512, NULL, compileInfoLog);
                String error = "Shader Program链接失败：";
                error += compileInfoLog;
                throw std::runtime_error(error.c_str());
        }
}

OpenGLShader::OpenGLShader(const char* alslFile)
{
        AlslSource source;
        anciu32    shaderv;
        anciu32    shaderf;
        const char *vstr;
        const char *fstr;


        ReadAlslSource(alslFile, &source);

        _program_id = glCreateProgram();
        shaderv = glCreateShader(GL_VERTEX_SHADER);
        shaderf = glCreateShader(GL_FRAGMENT_SHADER);

        /* 提交着色器源码并编译 */
        vstr = source.vtxSource.c_str();
        glShaderSource(shaderv, 1, &vstr, NULL);
        glCompileShader(shaderv);
        CheckCompileSuccessful(shaderv);

        fstr = source.fragSource.c_str();
        glShaderSource(shaderf, 1, &fstr, NULL);
        glCompileShader(shaderf);
        CheckCompileSuccessful(shaderf);

        glAttachShader(_program_id, shaderv);
        glAttachShader(_program_id, shaderf);
        glLinkProgram(_program_id);
        CheckLinkSuccessful(_program_id);

        /* 删除shader */
        glDeleteShader(shaderv);
        glDeleteShader(shaderf);
}

OpenGLShader::~OpenGLShader()
{
        glDeleteProgram(_program_id);
}

void OpenGLShader::Bind()
{
        glUseProgram(_program_id);
}

void OpenGLShader::SetInt(const char *name, int value)
{
        glUniform1i(glGetUniformLocation(_program_id, name), value);
}

void OpenGLShader::SetFloat(const char *name, float value)
{
        glUniform1f(glGetUniformLocation(_program_id, name), value);
}

void OpenGLShader::SetFloat2(const char *name, ancivec2 value)
{
        glUniform2f(glGetUniformLocation(_program_id, name), value.x, value.y);
}

void OpenGLShader::SetFloat3(const char *name, ancivec3 value)
{
        glUniform3f(glGetUniformLocation(_program_id, name), value.x, value.y, value.z);
}

void OpenGLShader::SetFloat4(const char *name, ancivec4 value)
{
        glUniform4f(glGetUniformLocation(_program_id, name), value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat3(const char *name, ancimat3 value)
{
        glUniformMatrix3fv(glGetUniformLocation(_program_id, name), 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGLShader::SetMat4(const char *name, ancimat4 value)
{
        glUniformMatrix4fv(glGetUniformLocation(_program_id, name), 1, GL_FALSE, glm::value_ptr(value));
}