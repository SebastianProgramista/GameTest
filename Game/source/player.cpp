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
#include "player.h"

//-----------------------------------------------
// Name:
// Desc:
//
Player::Player()
{
	m_fAngle = 0.0f;
	m_fPlayerSpeed = 60.0f;

	m_v2Magnitude = glm::vec2(0.0, 0.0);

	m_m4World = glm::mat4(1.0);

	m_fTimeToShoot = 0.4f;
	readyShoot = true;
}

//-----------------------------------------------
// Name:
// Desc:
//
Player::~Player()
{

}

//-----------------------------------------------
// Name:
// Desc:
//
void Player::init(glm::vec3 v3Pos, GLuint uiTextureID, Draw *pDraw)
{
	m_uiTextureID = uiTextureID;

	m_pDraw = pDraw;

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
Draw* Player::getDraw() const
{
	return m_pDraw;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Player::setTexture(GLuint uiTex)
{
	m_uiTextureID = uiTex;	
}

//-----------------------------------------------
// Name:
// Desc:
//
GLuint Player::getTexture()
{
	return m_uiTextureID;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Player::update()
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
void Player::setPosition(glm::vec3 v3Pos)
{
	m_v3Translate = v3Pos;
}

//-----------------------------------------------
// Name:
// Desc:
//
glm::vec3 Player::getPosition()
{
	glm::vec3 position = glm::vec3(1.0);
	position = glm::vec3(m_m4World[3].x, m_m4World[3].y, m_m4World[3].z);
	return position;
}


//-----------------------------------------------
// Name:
// Desc:
//
glm::mat4 Player::getWorld()
{
	return m_m4World;
}


//-----------------------------------------------
// Name:
// Desc:
//
void Player::setAction(ACTION action, float fTime)
{

	
	switch (action)
	{
	case ACTION::GRACZ_LEFT:
		m_v3Translate.x -= m_fPlayerSpeed * fTime;
		break;

	case ACTION::GRACZ_RIGHT:
		m_v3Translate.x += m_fPlayerSpeed * fTime;
		break;

	case ACTION::GRACZ_UP:
		m_v3Translate.y += m_fPlayerSpeed * fTime;
		break;

	case ACTION::GRACZ_DOWN:
		m_v3Translate.y -= m_fPlayerSpeed * fTime;
		break;

	default: 
		break;
	};

	return;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Player::setDirection(glm::vec2 v2MousePos)
{
	glm::vec2 player;

	player.x = m_v3Translate.x;
	player.y = m_v3Translate.y;

	m_v2Magnitude = v2MousePos - player;

	float angle = (float)glm::atan2(m_v2Magnitude.x, m_v2Magnitude.y);

	if (_isnan(angle)) return;

	angle = glm::degrees(angle);

	setRotate(-angle);
}

//-----------------------------------------------
// Name:
// Desc:
//
void Player::setRotate(float fAngle)
{
	m_fAngle = fAngle;
}


//-----------------------------------------------
// Name:
// Desc:
//
void Player::updateTimeShoot(float fTime)
{
	if (m_fTimeToShoot > 0.0)
	{
		m_fTimeToShoot -= fTime;
	}
	else
	{
		readyShoot = true;
		m_fTimeToShoot = 0.0f;
	}
}

//-----------------------------------------------
// Name:
// Desc:
//
bool Player::shotReady()
{
	if (readyShoot)
	{
		readyShoot = false;
		m_fTimeToShoot = 0.4f;
		return true;
	}

	return false;
}


//-----------------------------------------------
// Name:
// Desc:
//
glm::vec2 Player::getDirection() const
{
	glm::vec2 mag = glm::normalize(m_v2Magnitude);
	return mag;
}

//-----------------------------------------------
// Name:
// Desc:
//
float Player::getAngle() const
{
	return m_fAngle;
}