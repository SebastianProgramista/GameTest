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
#include "Weapon.h"

//-----------------------------------------------
// Name:
// Desc:
//
Weapon::Weapon()
{
	m_pDraw = NULL;

	m_m4World = glm::mat4(1.0);

	m_v3Translate = glm::vec3(0.0, 0.0, 0.0);
	m_v3Rotate = glm::vec3(0.0, 0.0, 1.0);
	m_v3Scale = glm::vec3(1.0, 1.0, 1.0);

	m_uiTextureID = 0;

	m_fAngle = 0.0f;
	m_fLife = 10.0f;
	m_fSpeed = 50.0f;
	m_fPower = 1.0f;

	m_bDead = false;
}

//-----------------------------------------------
// Name:
// Desc:
//
Weapon::~Weapon()
{

}

//-----------------------------------------------
// Name:
// Desc:
//
void Weapon::init(glm::vec3 v3Pos, GLuint uiTextureID, Draw *pDraw)
{
	m_pDraw = pDraw;

	m_uiTextureID = uiTextureID;

	m_v3Translate = v3Pos;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Weapon::updateMatrix()
{
	m_m4World = glm::mat4(1.0);

	m_m4World = glm::translate(m_m4World, m_v3Translate);
	m_m4World = glm::rotate(m_m4World, m_fAngle, m_v3Rotate);
	m_m4World = glm::scale(m_m4World, m_v3Scale);
}


//-----------------------------------------------
// Name:
// Desc:
//
void Weapon::update(float fTime)
{
	m_fLife -= fTime;
	if (m_fLife <= 0.0)
	{
		m_fLife = 0.0;
		m_bDead = true;
	}

	glm::vec2 newPos = m_v2Direction * m_fSpeed * fTime;
	m_v3Translate += glm::vec3(newPos.x, newPos.y, 0.0);

	updateMatrix();
}

//-----------------------------------------------
// Name:
// Desc:
//
void Weapon::setPosition(glm::vec3 v3Pos)
{
	m_v3Translate = v3Pos;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Weapon::setRotate(float fAngle)
{
	m_fAngle = fAngle;
}

//------------------------------------------
// setDirection
//------------------------------------------
void Weapon::setDirection(glm::vec2 v2Direction)
{
	m_v2Direction = v2Direction;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Weapon::setTexture(GLuint uiTex)
{
	m_uiTextureID = uiTex;
}

//-----------------------------------------------
// Name:
// Desc:
//
GLuint Weapon::getTexture()
{
	return m_uiTextureID;
}

//-----------------------------------------------
// Name:
// Desc:
//
glm::mat4 Weapon::getWorld()
{
	return m_m4World;
}

//-----------------------------------------------
// Name:
// Desc:
//
glm::vec3 Weapon::getPosition()
{
	return m_v3Translate;
}

//-----------------------------------------------
// Name:
// Desc:
//
Draw* Weapon::getDraw() const
{
	return m_pDraw;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Weapon::setDead(bool bDead)
{
	m_bDead = bDead;
}

//-----------------------------------------------
// Name:
// Desc:
//
bool Weapon::getIsDead() const
{
	return m_bDead;
}

//-----------------------------------------------
// Name:
// Desc:
//
float Weapon::getPower() const
{
	return m_fPower;
}


//-----------------------------------------------
// Name:
// Desc:
//
Gun::Gun()
{
	m_fLife = 5.0f;

	m_fSpeed = 200.0f;

	m_fPower = 2.0f;
}

//-----------------------------------------------
// Name:
// Desc:
//
Gun::~Gun()
{

}
