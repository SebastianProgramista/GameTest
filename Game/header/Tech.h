
#ifndef TECHNIQUE_H
#define	TECHNIQUE_H

#include "helper.h"

class Tech
{
public:

    Tech();
    virtual ~Tech();

    virtual bool Init();
	char *textFileRead(char *fn);
    void Enable();
	void Disable();

	GLint GetUniformLocation(const char* pUniformName);

	GLuint getShaderProg();
	void printProgramInfoLog(GLuint shader);

protected:
    bool AddShader(GLenum ShaderType, char* pShaderText);
    bool Finalize();

private:
    GLuint m_shaderProg;

};

#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF

#endif	
