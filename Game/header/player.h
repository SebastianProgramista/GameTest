
#ifndef PLAYER_H
#define PLAYER_H

#include "helper.h"


class Player
{

public:
	Player();
	~Player();
	
	void render();
	void update();
	void setPosition(glm::vec3 v3Pos);
	void init(glm::vec3 v3pos, glm::vec3 v3Rozm,glm::vec4 v4Textura,int iKierunek);
	
	void setTexture(GLuint uiTex);
	GLuint getTexture();
	glm::mat4 getWorld();
	glm::vec3 getPosition();
	glm::vec2 getDirection() const;


	void setRotate(float fAngle);

	void setAction(ACTION action, float fTime);
	void setDirection(glm::vec2 v2MousePos);


	void updateShoot();
	void updateTimeShoot(float fTime);
	bool shotReady();

	float getAngle() const;

private:
	struct Vertex
	{
		glm::vec3 m_pos;
		glm::vec2 m_tex;

		Vertex(){}

		Vertex(glm::vec3 pos, glm::vec2 tex)
		{
			m_pos = pos;
			m_tex = tex;

		}
	};
	
	void CreateVertexBuffer(glm::vec3 &rozm, glm::vec4 &tex);
	void CreateIndexBuffer();

	GLuint VBO;
	GLuint IBO;
	GLuint VAO;

	glm::mat4 m_m4World;

	glm::vec3 m_v3Translate;
	glm::vec3 m_v3Rotate;
	glm::vec3 m_v3Scale; 

	float m_fAngle;

	int m_iKierunekRot;

	GLuint m_uiTextureID;
	GLuint m_uiTextureShootID;


	glm::vec2 mag;

	float m_fTimeToShoot;
	bool readyShoot;

};//player

#endif