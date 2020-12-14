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
#include "Background.h"

//-----------------------------------------------
// Name:
// Desc:
//
Background::Background()
{
	m_pDraw = NULL;
	m_uiTextureID = 0;
}

//-----------------------------------------------
// Name:
// Desc:
//
Background::~Background()
{

}

//-----------------------------------------------
// Name:
// Desc:
//
void Background::init(glm::vec3 v3Pos, GLuint uiTextureID, Draw *pDraw)
{
	m_pDraw = pDraw;

	m_uiTextureID = uiTextureID;

	m_v3Translate = glm::vec3(v3Pos.x, v3Pos.y, v3Pos.z);
	m_v3Rotate = glm::vec3(0.0, 0.0, 1.0);
	m_v3Scale = glm::vec3(1.0, 1.0, 1.0);

	m_m4World = glm::mat4(1.0);

	m_m4World = glm::translate(m_m4World, m_v3Translate);
	m_m4World = glm::scale(m_m4World, m_v3Scale);

}
//-----------------------------------------------
// Name:
// Desc:
//
Draw* Background::getDraw() const
{
	return m_pDraw;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Background::setTexture(GLuint uiTex)
{
	m_uiTextureID = uiTex;
}

//-----------------------------------------------
// Name:
// Desc:
//
GLuint Background::getTexture()
{
	return m_uiTextureID;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Background::update()
{
	m_m4World = glm::mat4(1.0);

	m_m4World = glm::translate(m_m4World, m_v3Translate);

	m_m4World = glm::scale(m_m4World, m_v3Scale);
}

//-----------------------------------------------
// Name:
// Desc:
//
void Background::setPosition(glm::vec3 v3Pos)
{
	m_v3Translate = v3Pos;
}

//-----------------------------------------------
// Name:
// Desc:
//
glm::mat4 Background::getWorld()
{
	return m_m4World;
}