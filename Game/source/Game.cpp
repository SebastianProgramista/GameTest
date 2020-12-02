#include "Game.h"


//-----------------------------------------------
// Name:
// Desc:
//
GLuint Game::addTexture(const char* szFilename)
{
	Texture tex;
	glGenTextures(1, &tex.m_uiTextureID);
	glBindTexture(GL_TEXTURE_2D, tex.m_uiTextureID);

	tex.m_uiTextureID = SOIL_load_OGL_texture(szFilename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y
	);


	tex.m_iID = tex.m_uiTextureID;



	//if(glfwLoadTexture2D(szFilename, GLFW_BUILD_MIPMAPS_BIT))
	if (tex.m_iID != 0)
	{
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		v_vTexture.push_back(tex);
	}
	else
	{
		printf("Error load texture filename %s \n", szFilename);
		return -1;
	}

	return tex.m_uiTextureID;
}

//-----------------------------------------------
// Name:
// Desc:
//
Game::Game()
{
	m_dMouseX = 0;
	m_dMouseY = 0;
	m_iWindowWidth = 0;
	m_iWindowHeight = 0;

	m_uiTexture = 0;

	m_pWindow = NULL;
	m_pPlayer = NULL;
	m_pShader = NULL;
}

//-----------------------------------------------
// Name:
// Desc:
//
Game::~Game()
{
	for (unsigned int i = 0; i < v_vTexture.size(); ++i)
	{
		glDeleteTextures(1, &v_vTexture[i].m_uiTextureID);
	}

	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pPlayer);
}
//-----------------------------------------------
// Name:
// Desc:
//
void Game::init(GLFWwindow* window, glm::vec2& v2Resolution)
{

	m_pWindow = window;
	m_iWindowWidth = (int)v2Resolution.x;
	m_iWindowHeight = (int)v2Resolution.y;

	m_m4View = glm::ortho(0.0f, (float)v2Resolution.x, 0.0f, (float)v2Resolution.y, 1.0f, -1.0f);

	m_pShader = new ShaderTech();

	if (!m_pShader->Init())
	{
		printf("ERROR - shader load \n");
	}

	m_pShader->Enable();
	m_pShader->SetTextureUnit(0);
	m_pShader->Disable();

	m_pPlayer = new Player();

	if (!m_pPlayer)
	{
		return;
	}
	GLuint texPostac = addTexture("block02a.tga");

	m_pPlayer->init(glm::vec3(v2Resolution.x / 2, v2Resolution.y / 2, -0.5), glm::vec3(16, 16, 0), glm::vec4(0, 1, 1, 0), 1);
	m_pPlayer->setTexture(texPostac);

	glfwGetCursorPos(m_pWindow, &m_dMouseX, &m_dMouseY);

}
//-----------------------------------------------
// Name:
// Desc:
//
void Game::update(float fTime)
{

	glfwGetCursorPos(m_pWindow, &m_dMouseX, &m_dMouseY);

	m_dMouseY = m_iWindowHeight - m_dMouseY;

	if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT))
	{
		m_pPlayer->setAction(ACTION_LEFT, fTime);
	}
	else if (glfwGetKey(m_pWindow, GLFW_KEY_RIGHT))
	{
		m_pPlayer->setAction(ACTION_RIGHT, fTime);
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_UP))
	{
		m_pPlayer->setAction(ACTION_UP, fTime);
	}
	else if (glfwGetKey(m_pWindow, GLFW_KEY_DOWN))
	{
		m_pPlayer->setAction(ACTION_DOWN, fTime);
	}

	m_pPlayer->setDirection(glm::vec2(m_dMouseX, m_dMouseY));
	m_pPlayer->update();

}

//-----------------------------------------------
// Name:
// Desc:
//
void Game::render()
{
	m_pShader->Enable();

	glm::mat4 world2 = m_pPlayer->getWorld();
	glm::mat4 wvpWorld = m_m4View * world2;

	m_pShader->set(wvpWorld);

	m_pPlayer->render();

	m_pShader->Disable();
}