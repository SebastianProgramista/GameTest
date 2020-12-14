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
#include "Draw.h"

//-----------------------------------------------
// Name:
// Desc:
//
Draw::Draw()
{
	VBO = 0;
	IBO = 0;
	VAO = 0;
}

//-----------------------------------------------
// Name:
// Desc:
//
Draw::~Draw()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VAO);
}

//-----------------------------------------------
// Name:
// Desc:
//
void Draw::init(glm::vec3 v3Rozm, glm::vec4 v4Textura)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	m_v2Size = glm::vec2(v3Rozm.x, v3Rozm.y);

	CreateVertexBuffer(v3Rozm, v4Textura);
	CreateIndexBuffer();

	glBindVertexArray(0);

}

//-----------------------------------------------
// Name:
// Desc:
//
void Draw::CreateVertexBuffer(glm::vec3& rozm, glm::vec4& tex)
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
void Draw::CreateIndexBuffer()
{
	unsigned int Indices[] =
	{
	  0, 3, 2, 1
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
glm::vec2 Draw::getSize() const
{
	return m_v2Size;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Draw::render()
{
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}