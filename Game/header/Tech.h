//+++++++++++++++++++++++++++++++++++++++++++++++
// Projekt : Gra 2D
// Tech    : 
//           OpenGL 3.3/ GLSL 330, 
//           Glew 1.6, 
//           GLFW 3 
//           GLM 0.9.1.1
// http://www.sworek.acsoftware.pl   
//
//+++++++++++++++++++++++++++++++++++++++++++++++
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
