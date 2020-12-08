#ifndef WEAPON_H
#define WEAPON_H

#include "helper.h"
#include "Draw.h"

class Weapon
{
public:
	Weapon();
	virtual ~Weapon();
	void init(glm::vec3 v3Pos);

	void update(float fTime);
	void updateMatrix();

	void setPosition(glm::vec3 v3Pos);
	void setTexture(GLuint uiTex);
	void setRotate(float fAngle);
	void setDirection(glm::vec2 v2Direction);
	void setRender(Draw* pDraw);
	void setLife(float fLife);
	void setDead(bool bDead);

	GLuint getTexture();

	glm::mat4 getWorld();
	glm::vec3 getPosition();

	bool getIsDead() const;

	Draw* getDraw() const;
	Draw* m_pDraw;

	glm::mat4 m_m4World;

	glm::vec3 m_v3Translate;
	glm::vec3 m_v3Rotate;
	glm::vec3 m_v3Scale;

	glm::vec2 m_v2Direction;

	GLuint m_uiTextureID;

	float m_fAngle;
	float m_fLife;
	float m_fSpeed;

	bool m_bDead;

};//weapon


class Gun : public Weapon
{
public:
	Gun();
	~Gun();
};//Gun

#endif
