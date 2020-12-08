#include "Background.h"

//-----------------------------------------------
// Name:
// Desc:
//
Background::Background()
{
	VBO = 0;
	IBO = 0;
	VAO = 0;

}

//-----------------------------------------------
// Name:
// Desc:
//
Background::~Background()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VAO);
}

//-----------------------------------------------
// Name:
// Desc:
//
void Background::init(glm::vec3 v3Pos, glm::vec3 v3Rozm, glm::vec4 v4Textura)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	CreateVertexBuffer(v3Rozm, v4Textura);
	CreateIndexBuffer();

	glBindVertexArray(0);

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
void Background::CreateVertexBuffer(glm::vec3& rozm, glm::vec4& tex)
{
	Vertex Vertices[4] = {

		Vertex(glm::vec3(-rozm.x,  -rozm.y, rozm.z), glm::vec2(tex.x,tex.w)),
		Vertex(glm::vec3(rozm.x,  -rozm.y, rozm.z), glm::vec2(tex.y,tex.w)),
		Vertex(glm::vec3(rozm.x,   rozm.y, rozm.z), glm::vec2(tex.y,tex.z)),
		Vertex(glm::vec3(-rozm.x,   rozm.y, rozm.z), glm::vec2(tex.x,tex.z))
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

}

//-----------------------------------------------
// Name:
// Desc:
//
void Background::CreateIndexBuffer()
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
void Background::render()
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