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

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Helper.h"

class Texture
{

public:
	Texture();
	virtual ~Texture();
	GLuint addTexture(const char* szFilename);

private:
	std::vector<GLuint> v_vTexture;
	GLuint m_uiTextureID;
};

#endif