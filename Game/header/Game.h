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

#ifndef GAME_H
#define GAME_H

#include "helper.h"
#include "player.h"
#include "Shader.h"

#include "Weapon.h"
#include "Background.h"
#include "Texture.h"
#include "Enemy.h"

class Game
{
public:

	Game();
	~Game();

	void render();
	void update(float fTime);
	void setPosition(glm::vec3 v3Pos);
	
	bool init(GLFWwindow* window, glm::vec2& v2Resolution);

	bool createBackground();
	bool createPlayer();
	bool createEnemy();
	bool createGunBulletObject();



	void updateShootGun(float fTime);
	void addBullet(float fTime);


	void generateEnemy(float fTime);

	void updatePlayer(float fTime);
	void updateEnemy(float fTime);

	bool collideEnemtToEnemy(glm::vec3 newPositionEnemy, int iIdEnemy);


private:
	GLFWwindow *m_pWindow;

	ShaderTech *m_pShader;
	Texture    *m_pTexture;

	double m_dMouseX, m_dMouseY;
	int m_iWindowWidth, m_iWindowHeight;


	Draw       *m_pDrawBackground;
	Background *m_pBackground;
	GLuint      m_uiTextureBackground;

	Player     *m_pPlayer;
	Draw       *m_pDrawPlayer;
	GLuint      m_uiTexturePlayer;


	//--
	std::vector<Enemy> v_vEnemy;

	Draw* m_pDrawZombie;
	GLuint m_uiTextureZombie;


	//--
	float sf_TimeForEnemyCreate;
	float sf_TimeCreateEnemy;


	std::vector<Weapon> v_vWeapon;
	Draw* m_pDrawBullet;
	GLuint m_uiTextureGunBullet;

	glm::mat4 m_m4View;

};//Box

#endif