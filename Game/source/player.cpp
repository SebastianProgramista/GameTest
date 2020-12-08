#include "player.h"

//-----------------------------------------------
// Name:
// Desc:
//
Player::Player()
{
	VBO            = 0;
	IBO            = 0;
	VAO            = 0;
	m_fAngle       = 0.0f;
	m_iKierunekRot = 0;


	m_fTimeToShoot = 0.2f;
}

//-----------------------------------------------
// Name:
// Desc:
//
Player::~Player()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VAO);
}

//-----------------------------------------------
// Name:
// Desc:
//
void Player::init(glm::vec3 v3Pos, glm::vec3 v3Rozm,glm::vec4 v4Textura, int iKierunek)
{
	glGenVertexArrays(1, &VAO); 
	glBindVertexArray(VAO);

	CreateVertexBuffer(v3Rozm, v4Textura);
	CreateIndexBuffer();

	glBindVertexArray(0);

	m_v3Translate = glm::vec3(v3Pos.x,v3Pos.y,v3Pos.z);
	m_v3Rotate    = glm::vec3(0.0,0.0,1.0);
	m_v3Scale     = glm::vec3(1.0,1.0,1.0);
		
	m_iKierunekRot = iKierunek;

	m_m4World  = glm::mat4(1.0);

	m_m4World = glm::translate(m_m4World, m_v3Translate);
	m_m4World = glm::scale(m_m4World, m_v3Scale);
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
void Player::setAction(ACTION action, float fTime)
{
	switch(action)
	{
		case ACTION_LEFT:
			m_v3Translate.x -= 30.0f*fTime;
			break;

		case ACTION_RIGHT:
			m_v3Translate.x += 30.0f*fTime;
			break;

		case ACTION_UP:
			m_v3Translate.y += 30.0f*fTime;
			break;

		case ACTION_DOWN:
			m_v3Translate.y -= 30.0f*fTime;
			break;
	}
}

//------------------------------------------------
// updateTimeShoot
//------------------------------------------------
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

//------------------------------------------------
// updateShoot
//------------------------------------------------
void Player::updateShoot()
{
		m_fTimeToShoot = 0.2;
}

//------------------------------------------------
// shotReady
//------------------------------------------------
bool Player::shotReady()
{
	if (readyShoot)
	{
		readyShoot = false;
		m_fTimeToShoot = 0.2f;
		return true;
	}

	return false;
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

	mag = v2MousePos - player;
	mag = glm::normalize(mag);

	float angle = (float)glm::atan2(mag.x, mag.y);
	
	if(_isnan(angle)) return;
	
	angle = glm::degrees(angle);
	
	setRotate(-angle);
}

//------------------------------------------------
// getDirection
//------------------------------------------------
glm::vec2 Player::getDirection() const
{
	return mag;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Player::CreateVertexBuffer(glm::vec3 &rozm, glm::vec4 &tex)
{
	Vertex Vertices[4] = {
		
		Vertex(glm::vec3( -rozm.x,  -rozm.y, rozm.z), glm::vec2(tex.x,tex.w)),
		Vertex(glm::vec3(  rozm.x,  -rozm.y, rozm.z), glm::vec2(tex.y,tex.w)),
	    Vertex(glm::vec3(  rozm.x,   rozm.y, rozm.z), glm::vec2(tex.y,tex.z)),
		Vertex(glm::vec3( -rozm.x,   rozm.y, rozm.z), glm::vec2(tex.x,tex.z))
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)12);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)20);

}//crete vertex buffer

//-----------------------------------------------
// Name:
// Desc:
//
void Player::CreateIndexBuffer()
{
	unsigned int Indices[] = 
	{ 
	  0, 3, 2,  0, 2, 1
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
}

//-----------------------------------------------
// Name:
// Desc:
//
void Player::render()
{
	glBindTexture(GL_TEXTURE_2D, m_uiTextureID);
	
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
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
		m_m4World = glm::scale(m_m4World,m_v3Scale);
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
void Player::setRotate(float fAngle)
{
	m_fAngle = fAngle;
}


//------------------------------------------
//
//------------------------------------------
float Player::getAngle() const
{
	return m_fAngle;
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