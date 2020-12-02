#ifndef GAME_H
#define GAME_H

#include "helper.h"
#include "player.h"
#include "Shader.h"

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

	ShaderTech* m_pShader;
	Player* m_pPlayer;

	glm::mat4 m_m4View;
	GLFWwindow* m_pWindow;

private:

	double m_dMouseX, m_dMouseY;
	int m_iWindowWidth, m_iWindowHeight;

	GLuint m_uiTexture;
};//Box

#endif