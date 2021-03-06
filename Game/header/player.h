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

#ifndef PLAYER_H
#define PLAYER_H

#include "helper.h"
#include "Draw.h"

class Player
{

public:
	Player();
	virtual ~Player();
	
	void update();
	void setPosition(glm::vec3 v3Pos);
	void init(glm::vec3 v3pos, GLuint uiTextureID, Draw* pDraw);
	
	void setTexture(GLuint uiTex);
	GLuint getTexture();


	glm::mat4 getWorld();
	glm::vec3 getPosition();

	Draw* getDraw() const;

	void setAction(ACTION action, float fTime);

	void setDirection(glm::vec2 v2MousePos);
	void setRotate(float fAngle);

	void updateTimeShoot(float fTime);

	bool shotReady();

	glm::vec2 getDirection() const;

	float getAngle() const;


private:
	glm::mat4 m_m4World;

	glm::vec3 m_v3Translate;
	glm::vec3 m_v3Rotate;
	glm::vec3 m_v3Scale;

	GLuint m_uiTextureID;

	float m_fAngle;

	Draw* m_pDraw;


	float m_fPlayerSpeed;

	glm::vec2 m_v2Magnitude;

	float m_fTimeToShoot;
	bool readyShoot;

};//player

#endif