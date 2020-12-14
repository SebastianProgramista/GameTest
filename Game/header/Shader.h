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

#ifndef SHADERTECH_H
#define	SHADERTECH_H

#include "Tech.h"

class ShaderTech : public Tech 
{
public:

    ShaderTech();
    virtual bool Init();
	void set(glm::mat4 &m4World);
	void SetTextureUnit(unsigned int uiTextureUnit);

private:
   
	GLuint m_WVPLocation;
    GLuint m_WorldMatrixLocation;
    GLuint m_samplerLocation;
};

#endif