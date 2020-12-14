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

#include "Texture.h"

//-----------------------------------------------
// Name:
// Desc:
//
Texture::Texture()
{
	m_uiTextureID = 0;
}

//-----------------------------------------------
// Name:
// Desc:
//
Texture::~Texture()
{
	for (unsigned int i = 0; i < v_vTexture.size(); ++i)
	{
		glDeleteTextures(1, &v_vTexture[i]);
	}

	v_vTexture.clear();
}

//-----------------------------------------------
// Name:
// Desc:
//
GLuint Texture::addTexture(const char* szFilename)
{

	glGenTextures(1, &m_uiTextureID);
	glBindTexture(GL_TEXTURE_2D, m_uiTextureID);

	m_uiTextureID = SOIL_load_OGL_texture(szFilename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y
	);


	if (m_uiTextureID != 0)
	{
		v_vTexture.push_back(m_uiTextureID);
	}
	else
	{
		printf("Error load texture filename %s \n", szFilename);
		return -1;
	}

	return m_uiTextureID;

}