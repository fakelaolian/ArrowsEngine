/* AUTHOR: 2BKBD, DATE: 2022/1/10 */
#pragma once

#include <RHI/RHI.h>

class OpenGLShader : public VRHIShader{
public:
        explicit OpenGLShader  (const char* alslFile);
        ~OpenGLShader ();
        void Bind     ()                                 override;
        void SetInt   (const char *name, int      value) override;
        void SetFloat (const char *name, float    value) override;
        void SetFloat2(const char *name, ancivec2 value) override;
        void SetFloat3(const char *name, ancivec3 value) override;
        void SetFloat4(const char *name, ancivec4 value) override;
        void SetMat3  (const char *name, ancimat3 value) override;
        void SetMat4  (const char *name, ancimat4 value) override;

private:
        anciu32 _program_id;
};