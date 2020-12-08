#ifndef GAME_H
#define GAME_H

#include "helper.h"
#include "player.h"
#include "Shader.h"

#include "Weapon.h"
#include "Background.h"


class Game
{
public:

	Game();
	~Game();

	struct Texture
	{
		GLuint m_uiTextureID;
		int m_iID;
	};

	std::vector<Texture> v_vTexture;

	GLuint addTexture(const char* szFilename);

	void render();
	void update(float fTime);
	void setPosition(glm::vec3 v3Pos);
	void init(GLFWwindow* window, glm::vec2& v2Resolution);

	glm::mat4 m_m4View;
	

private:
	GLFWwindow* m_pWindow;

	ShaderTech* m_pShader;
	Player* m_pPlayer;

	std::vector<Weapon> v_vWeapon;

	double m_dMouseX, m_dMouseY;
	int m_iWindowWidth, m_iWindowHeight;

	GLuint m_uiTexture;
	GLuint m_uiTexGunBullet;
	GLuint m_uiTexBackground;
	GLuint texPostac, texPostacShoot;

	Draw* pDrawGunBullet;
	Background* pBackground;


	bool m_bShootReady;

};//Box

#endif