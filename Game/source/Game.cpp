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


	if (tex.m_iID != 0)
	{
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


	v_vWeapon.clear();


	m_pWindow = NULL;
	m_pPlayer = NULL;
	m_pShader = NULL;


	pBackground = NULL;
	pDrawGunBullet = NULL;

}

//-----------------------------------------------
// Name:
// Desc:
//
Game::~Game()
{
	v_vWeapon.clear();


	for (unsigned int i = 0; i < v_vTexture.size(); ++i)
	{
		glDeleteTextures(1, &v_vTexture[i].m_uiTextureID);
	}

	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pPlayer);

	SAFE_DELETE(pBackground);
	SAFE_DELETE(pDrawGunBullet);

}
//-----------------------------------------------
// Name:
// Desc:
//
void Game::init(GLFWwindow* window, glm::vec2& v2Resolution)
{

	m_bShootReady = false;

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


	texPostac = addTexture("Machiner.tga");
	texPostacShoot = addTexture("Machiner2.tga");
	m_uiTexGunBullet = addTexture("gunbullet.tga");
	m_uiTexBackground = addTexture("background.tga");


	m_pPlayer = new Player();

	if (!m_pPlayer)
	{
		return;
	}

	m_pPlayer->init(glm::vec3(v2Resolution.x / 2, v2Resolution.y / 2, -0.5), glm::vec3(16, 16, 0), glm::vec4(0, 1, 1, 0), 1);
	m_pPlayer->setTexture(texPostac);



	pBackground = new Background();
	if (!pBackground)
	{
		return;
	}
	pBackground->init(glm::vec3(m_iWindowWidth / 2, m_iWindowHeight / 2, -0.5), glm::vec3(m_iWindowWidth, m_iWindowHeight, 0.0), glm::vec4(0.0, 1.0, 1.0, 0.0));
	pBackground->setTexture(m_uiTexBackground);


	pDrawGunBullet = new Draw();
	if (!pDrawGunBullet)
	{
		return;
	}
	pDrawGunBullet->init(glm::vec3(4.0, 6.0, 0.0), glm::vec4(0.0, 1.0, 1.0, 0.0));



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


	if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_1))
	{
		Gun gun;
		if (m_pPlayer->shotReady())
		{
			glm::vec3 position = m_pPlayer->getPosition();
			glm::vec2 kierunek = m_pPlayer->getDirection();

			position += glm::vec3(kierunek.x, kierunek.y, 0.0) * glm::vec3(20, 20, 0);

			gun.init(position);
			gun.setDirection(kierunek);
			gun.setRotate(m_pPlayer->getAngle());
			gun.setRender(pDrawGunBullet);
			gun.setTexture(m_uiTexGunBullet);
			gun.updateMatrix();
			v_vWeapon.push_back(gun);

			m_bShootReady = true;
		}
	}

	m_pPlayer->setDirection(glm::vec2(m_dMouseX, m_dMouseY));
	m_pPlayer->updateTimeShoot(fTime);
	m_pPlayer->update();


	for (unsigned int i = 0; i < v_vWeapon.size(); ++i)
	{
		if (v_vWeapon[i].getIsDead())
		{
			DeleteFromVector(v_vWeapon, i);
		}
	}


	for (unsigned int i = 0; i < v_vWeapon.size(); ++i)
	{
		if (!v_vWeapon[i].getIsDead())
		{
			v_vWeapon[i].update(fTime);

			glm::vec3 mPos = v_vWeapon[i].getPosition();

			if (mPos.x > m_iWindowWidth || mPos.x < 0 || mPos.y > m_iWindowHeight || mPos.y < 0)
			{
				v_vWeapon[i].setDead(true);
			}
		}
	}
}

//-----------------------------------------------
// Name:
// Desc:
//
void Game::render()
{
	GLuint tex = 0;

	m_pShader->Enable();

	glm::mat4 wvpWorld = m_m4View * glm::mat4(1.0);

	m_pShader->set(wvpWorld);
	pBackground->render();

	glEnable(GL_BLEND);
	glm::mat4 world2 = m_pPlayer->getWorld();
	wvpWorld = m_m4View * world2;

	m_pShader->set(wvpWorld);

	if (m_bShootReady)
	{
		m_pPlayer->setTexture(texPostacShoot);
		m_bShootReady = false;
	}
	else
	{
		m_pPlayer->setTexture(texPostac);
	}
	m_pPlayer->render();

	for (unsigned int i = 0; i < v_vWeapon.size(); ++i)
	{
		if (tex != v_vWeapon[i].getTexture())
		{
			tex = v_vWeapon[i].getTexture();
			glBindTexture(GL_TEXTURE_2D, tex);
		}
		wvpWorld = v_vWeapon[i].getWorld();
		wvpWorld = m_m4View * wvpWorld;
		m_pShader->set(wvpWorld);
		v_vWeapon[i].getDraw()->render();
	}
	glDisable(GL_BLEND);

	m_pShader->Disable();
}