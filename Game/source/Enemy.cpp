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

#include "Enemy.h"

//-----------------------------------------------
// Name:
// Desc:
//
Enemy::Enemy()
{
	m_pDraw = NULL;

	m_m4World = glm::mat4(1.0);

	m_v3Translate = glm::vec3(0.0, 0.0, 0.0);
	m_v3Rotate = glm::vec3(0.0, 0.0, 1.0);
	m_v3Scale = glm::vec3(1.0, 1.0, 1.0);

	m_uiTextureID = 0;

	m_fAngle = 0;

	m_v2Direction = glm::vec2(0.0, 0.0);

	m_fSpeed = 1.0f;

}

//-----------------------------------------------
// Name:
// Desc:
//
Enemy::~Enemy()
{

}

//-----------------------------------------------
// Name:
// Desc:
//
void Enemy::init(glm::vec3 v3Pos, GLuint uiTextureID, Draw* pDraw)
{
	m_uiTextureID = uiTextureID;
	m_pDraw = pDraw;
	m_v3Translate = v3Pos;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Enemy::updateMatrix()
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
void Enemy::setPosition(glm::vec3 v3Pos)
{
	m_v3Translate = v3Pos;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Enemy::setTexture(GLuint uiTex)
{
	m_uiTextureID = uiTex;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Enemy::setRotate(float fAngle)
{
	m_fAngle = fAngle;
}

//-----------------------------------------------
// Name:
// Desc:
//
GLuint Enemy::getTexture()
{
	return m_uiTextureID;
}

//-----------------------------------------------
// Name:
// Desc:
//
glm::mat4 Enemy::getWorld()
{
	return m_m4World;
}
//-----------------------------------------------
// Name:
// Desc:
//
glm::vec3 Enemy::getPosition()
{
	return m_v3Translate;
}

//-----------------------------------------------
// Name:
// Desc:
//
Draw* Enemy::getDraw() const
{
	return m_pDraw;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Enemy::update(float fTime)
{
	glm::vec2 newPos = m_v2Direction * m_fSpeed * fTime;

	glm::vec2 mPosEnemy = glm::vec2(m_v3Translate.x, m_v3Translate.y);
	if (Distance(m_v2PlayerPosition, mPosEnemy) > 48.0f)
	{
		m_v3Translate += glm::vec3(newPos.x, newPos.y, 0.0);
	}

	updateMatrix();
}
//-----------------------------------------------
// Name:
// Desc:
//
void Enemy::updateDirection(glm::vec2 v2PlayerPos)
{
	glm::vec2 player;

	player.x = m_v3Translate.x;
	player.y = m_v3Translate.y;

	m_v2PlayerPosition = v2PlayerPos;

	glm::vec2 mag = v2PlayerPos - player;
	mag = glm::normalize(mag);

	m_v2Direction = mag;

	float angle = (float)glm::atan2(mag.x, mag.y);

	if (_isnan(angle)) return;

	angle = glm::degrees(angle);

	setRotate(-angle);
}

//-----------------------------------------------
// Name:
// Desc:
//
Zombie::Zombie()
{
	m_fSpeed = 45.0f;
}

//-----------------------------------------------
// Name:
// Desc:
//
Zombie::~Zombie()
{

}