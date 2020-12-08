#ifndef DRAW_H
#define DRAW_H

#include "helper.h"


class Draw
{

public:
	Draw();
	~Draw();

	void render();
	void init(glm::vec3 v3Rozm, glm::vec4 v4Textura);

	glm::vec2 getSize() const;

private:
	struct Vertex
	{
		glm::vec3 m_pos;
		glm::vec2 m_tex;

		Vertex() {}

		Vertex(glm::vec3 pos, glm::vec2 tex)
		{
			m_pos = pos;
			m_tex = tex;

		}
	};

	void CreateVertexBuffer(glm::vec3& rozm, glm::vec4& tex);
	void CreateIndexBuffer();

	GLuint VBO;
	GLuint IBO;
	GLuint VAO;

	glm::vec2 m_v2Size;

};//draw
#endif