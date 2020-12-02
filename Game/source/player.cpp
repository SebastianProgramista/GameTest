#include "player.h"

//------------------------------------------------
// constructor
//------------------------------------------------
Player::Player()
{
	VBO            = 0;
	IBO            = 0;
	VAO            = 0;
	m_fAngle       = 0.0f;
	m_iKierunekRot = 0;
}

//------------------------------------------------
// destructor
//------------------------------------------------
Player::~Player()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VAO);
}

//------------------------------------------------
// Init
//------------------------------------------------
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

//------------------------------------------------
// Set texture
//------------------------------------------------
void Player::setTexture(GLuint uiTex)
{
	m_uiTextureID = uiTex;	
}

//------------------------------------------------
// Get texture id
//------------------------------------------------
GLuint Player::getTexture()
{
	return m_uiTextureID;
}

//------------------------------------------------
// Get texture id
//------------------------------------------------
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
// Get texture id
//------------------------------------------------
void Player::setDirection(glm::vec2 v2MousePos)
{
	glm::vec2 player;

	player.x = m_v3Translate.x;
	player.y = m_v3Translate.y;

	glm::vec2 mag = v2MousePos - player;
	          mag = glm::normalize(mag);

	float angle = (float)glm::atan2(mag.x, mag.y);
	
	if(_isnan(angle)) return;
	
	angle = glm::degrees(angle);
	
	setRotate(-angle);
}

//------------------------------------------------
// Create vertex buffer
//------------------------------------------------
void Player::CreateVertexBuffer(glm::vec3 &rozm, glm::vec4 &tex)
{
	Vertex Vertices[4] = {
		
		//offset tex.x = pozycja x
		// tex.y = pozycjax uwzglêdniajaca szerokoœæ
		// tex.z = pozycja y
		// tex.w pozycja y uwzglêdniajaca wysokoœæ

		/*
			texX texW  --------  texY texW
					   |	  |
			texX texZ  --------  texY texZ	
		*/
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

//------------------------------------------------
// Create vertex buffer
//------------------------------------------------
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

//------------------------------------------------
// Render
//------------------------------------------------
void Player::render()
{
	glBindTexture(GL_TEXTURE_2D, m_uiTextureID);

	glEnable(GL_BLEND);
	
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);

	glDisable(GL_BLEND);

}
//------------------------------------------------
// Update
//------------------------------------------------
void Player::update()
{
	   	m_m4World = glm::mat4(1.0);
		
		m_m4World = glm::translate(m_m4World, m_v3Translate);
		m_m4World = glm::rotate(m_m4World, m_fAngle, m_v3Rotate);
		m_m4World = glm::scale(m_m4World,m_v3Scale);
}

//------------------------------------------------
// setPosition
//------------------------------------------------
void Player::setPosition(glm::vec3 v3Pos)
{
	m_v3Translate = v3Pos;
}

//------------------------------------------------
// setPosition
//------------------------------------------------
void Player::setRotate(float fAngle)
{
	m_fAngle = fAngle;
}

//------------------------------------------------
// getPosition
//------------------------------------------------
glm::vec3 Player::getPosition()
{
	glm::vec3 position = glm::vec3(1.0);
	position = glm::vec3(m_m4World[3].x, m_m4World[3].y, m_m4World[3].z);
	return position;
}
//------------------------------------------------
// getAABB
//------------------------------------------------
/*glm::vec3 Hud::getAABB()
{
	return BoundingBox;
}*/
//------------------------------------------------
// getWorld
//------------------------------------------------
glm::mat4 Player::getWorld()
{
  return m_m4World;
}