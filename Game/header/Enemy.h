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

#ifndef ENEMY_H
#define ENEMY_H

#include "helper.h"
#include "Draw.h"

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();
	void init(glm::vec3 v3Pos, GLuint uiTextureID, Draw* pDraw);
	void update(float fTime);
	void updateMatrix();
	void setPosition(glm::vec3 v3Pos);
	void setTexture(GLuint uiTex);
	void setRotate(float fAngle);

	GLuint getTexture();

	glm::mat4 getWorld();
	glm::vec3 getPosition();

	Draw* getDraw() const;
	Draw* m_pDraw;

	void updateDirection(glm::vec2 v2PlayerPos);

	glm::mat4 m_m4World;

	glm::vec3 m_v3Translate;
	glm::vec3 m_v3Rotate;
	glm::vec3 m_v3Scale;

	GLuint m_uiTextureID;

	float m_fAngle;


	glm::vec2 m_v2Direction;
	float m_fSpeed;

	glm::vec2 m_v2PlayerPosition;
};//enemy


class Zombie : public Enemy
{
public:
	Zombie();
	~Zombie();
};//zombie

#endif