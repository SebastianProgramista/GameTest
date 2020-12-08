#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "helper.h"


class Background
{

public:
	Background();
	~Background();

	void render();
	void update();
	void setPosition(glm::vec3 v3Pos);
	void init(glm::vec3 v3pos, glm::vec3 v3Rozm, glm::vec4 v4Textura);

	void setTexture(GLuint uiTex);
	GLuint getTexture();
	glm::mat4 getWorld();

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

	glm::mat4 m_m4World;

	glm::vec3 m_v3Translate;
	glm::vec3 m_v3Rotate;
	glm::vec3 m_v3Scale;

	GLuint m_uiTextureID;

};//background

#endif