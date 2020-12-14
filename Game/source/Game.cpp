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
#include "Game.h"



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

	m_pBackground = NULL;
	m_pDrawBackground = NULL;
	m_uiTextureBackground = 0;

	m_pDrawPlayer = NULL;
	m_pPlayer = NULL;
	m_uiTexturePlayer = 0;

	m_pShader = NULL;
	m_pTexture = NULL;
	m_pWindow = NULL;

	v_vEnemy.clear();

	sf_TimeForEnemyCreate = 2.0;
	sf_TimeCreateEnemy = 0.0f;

	m_pDrawZombie = NULL;
	m_uiTextureZombie = 0;

	m_pDrawBullet = NULL;
	m_uiTextureGunBullet = 0;

}

//-----------------------------------------------
// Name:
// Desc:
//
Game::~Game()
{
	v_vWeapon.clear();

	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pShader);

	SAFE_DELETE(m_pBackground);
	SAFE_DELETE(m_pDrawBackground);

	SAFE_DELETE(m_pDrawPlayer);
	SAFE_DELETE(m_pPlayer);

	SAFE_DELETE(m_pDrawZombie);

	SAFE_DELETE(m_pDrawBullet);

	v_vEnemy.clear();

}
//-----------------------------------------------
// Name:
// Desc:
//
bool Game::init(GLFWwindow* window, glm::vec2& v2Resolution)
{

	m_pWindow = window;
	m_iWindowWidth = (int)v2Resolution.x;
	m_iWindowHeight = (int)v2Resolution.y;

	m_m4View = glm::ortho(0.0f, (float)v2Resolution.x, 0.0f, (float)v2Resolution.y, -1.0f, 1.0f);

	m_pShader = new ShaderTech();

	if (!m_pShader->Init())
	{
		printf("ERROR - shader load \n");
	}

	m_pShader->Enable();
	m_pShader->SetTextureUnit(0);
	m_pShader->Disable();


	m_pTexture = new Texture();
	if (!m_pTexture)
	{
		return false;
	}

	// t³o
	if (!createBackground())
	{
		return false;
	}

	// gracz
	if (!createPlayer())
	{
		return false;
	}

	// enemy
	if (!createEnemy())
	{
		return false;
	}

	//tworzenie obiektu bullet 
	if (!createGunBulletObject())
	{
		return false;
	}

	glfwGetCursorPos(m_pWindow, &m_dMouseX, &m_dMouseY);


	return true;

}

//-----------------------------------------------
// Name:
// Desc:
//
bool Game::createBackground()
{


	m_uiTextureBackground = m_pTexture->addTexture("texture/background.tga");

	m_pDrawBackground = new Draw();
	if (!m_pDrawBackground)
	{
		return false;
	}
	m_pDrawBackground->init(glm::vec3(m_iWindowWidth / 2, m_iWindowHeight / 2, 0.0), glm::vec4(0.0, 1.0, 1.0, 0.0));


	m_pBackground = new Background();
	if (!m_pBackground)
	{
		return false;
	}
	m_pBackground->init(glm::vec3(m_iWindowWidth / 2, m_iWindowHeight / 2, -0.5), m_uiTextureBackground, m_pDrawBackground);

	m_pBackground->update();

	return true;
}

//-----------------------------------------------
// Name:
// Desc:
//
bool Game::createPlayer()
{
	m_uiTexturePlayer = m_pTexture->addTexture("texture/soldier.tga");

	m_pDrawPlayer = new Draw();
	if (!m_pDrawPlayer)
	{
		return false;
	}
	m_pDrawPlayer->init(glm::vec3(16, 16, 0.0), glm::vec4(0.0, 1.0, 1.0, 0.0));


	m_pPlayer = new Player();
	if (!m_pPlayer)
	{
		return false;
	}
	m_pPlayer->init(glm::vec3(m_iWindowWidth / 2, m_iWindowHeight / 2, 0.5), m_uiTexturePlayer, m_pDrawPlayer);

	m_pPlayer->update();

	return true;
}

//-----------------------------------------------
// Name:
// Desc:
//
bool Game::createEnemy()
{
	m_uiTextureZombie = m_pTexture->addTexture("texture/enemy.tga");

	m_pDrawZombie = new Draw();
	if (!m_pDrawZombie)
	{
		return false;
	}
	m_pDrawZombie->init(glm::vec3(16, 16, 0.5), glm::vec4(0.0, 1.0, 1.0, 0.0));

	return true;
}

//-----------------------------------------------
// Name:
// Desc:
//
bool Game::createGunBulletObject()
{
	m_uiTextureGunBullet = m_pTexture->addTexture("texture/bullet.tga");

	m_pDrawBullet = new Draw();
	if (!m_pDrawBullet)
	{
		return false;
	}

	m_pDrawBullet->init(glm::vec3(3, 6, 0.5), glm::vec4(0.3, 0.7, 1.0, 0.0));

	return true;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Game::generateEnemy(float fTime)
{
	if (v_vEnemy.size() < 20)
	{

		if (sf_TimeCreateEnemy < sf_TimeForEnemyCreate)
		{
			sf_TimeCreateEnemy += fTime;
		}
		else
		{
			sf_TimeCreateEnemy = 0.0f;

			Zombie mZombie;

			int pos = rand() % 4 + 1;

			if (pos == 1)
			{
				int posX = rand() % m_iWindowWidth;
				mZombie.init(glm::vec3(posX, -16.0, 0.5), m_uiTextureZombie, m_pDrawZombie);
			}
			else if (pos == 2)
			{
				int posX = rand() % m_iWindowWidth;
				mZombie.init(glm::vec3(posX, m_iWindowHeight + 16.0f, 0.5), m_uiTextureZombie, m_pDrawZombie);
			}
			else if (pos == 3)
			{
				int posY = rand() % m_iWindowHeight;
				mZombie.init(glm::vec3(-16.0f, posY, 0.5), m_uiTextureZombie, m_pDrawZombie);
			}
			else if (pos == 4)
			{
				int posY = rand() % m_iWindowHeight;
				mZombie.init(glm::vec3(m_iWindowWidth + 16.0f, posY, 0.5), m_uiTextureZombie, m_pDrawZombie);
			}

			mZombie.updateMatrix();
			v_vEnemy.push_back(mZombie);
		}
	}
}

//-----------------------------------------------
// Name:
// Desc:
//
void Game::updatePlayer(float fTime)
{

	glfwGetCursorPos(m_pWindow, &m_dMouseX, &m_dMouseY);

	m_dMouseY = m_iWindowHeight - m_dMouseY;

	if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT))
	{
		m_pPlayer->setAction(ACTION::GRACZ_LEFT, fTime);
	}
	else if (glfwGetKey(m_pWindow, GLFW_KEY_RIGHT))
	{
		m_pPlayer->setAction(ACTION::GRACZ_RIGHT, fTime);
	}

	if (glfwGetKey(m_pWindow, GLFW_KEY_UP))
	{
		m_pPlayer->setAction(ACTION::GRACZ_UP, fTime);
	}
	else if (glfwGetKey(m_pWindow, GLFW_KEY_DOWN))
	{
		m_pPlayer->setAction(ACTION::GRACZ_DOWN, fTime);
	}


	m_pPlayer->setDirection(glm::vec2(m_dMouseX, m_dMouseY));
	m_pPlayer->updateTimeShoot(fTime);
	m_pPlayer->update();

	if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_1))
	{
		if (m_pPlayer->shotReady())
		{
			addBullet(fTime);
		}
	}
}

//-----------------------------------------------
// Name:
// Desc:
//
void Game::update(float fTime)
{

	updatePlayer(fTime);

	updateShootGun(fTime);

	generateEnemy(fTime);

	updateEnemy(fTime);


}
//-----------------------------------------------
// Name:
// Desc:
//
void Game::addBullet(float fTime)
{

	Gun gun;

	glm::vec3 position = m_pPlayer->getPosition();

	glm::vec2 kierunek = m_pPlayer->getDirection();

	position += glm::vec3(kierunek.x, kierunek.y, 0.0) * glm::vec3(20, 20, 0);

	gun.init(position, m_uiTextureGunBullet, m_pDrawBullet);

	gun.setDirection(kierunek);

	gun.setRotate(m_pPlayer->getAngle());

	gun.updateMatrix();

	v_vWeapon.push_back(gun);
}

//-----------------------------------------------
// Name:
// Desc:
//
bool Game::collideEnemtToEnemy(glm::vec3 newPositionEnemy, int iIdEnemy)
{
	for (unsigned int i = 0; i < v_vEnemy.size(); ++i)
	{
		if (iIdEnemy != i)
		{
			glm::vec3 posEnemy = v_vEnemy[i].getPosition();

			if (Collide(glm::vec3(16, 16, 0), glm::vec3(16, 16, 0), newPositionEnemy, posEnemy))
			{
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------
// Name:
// Desc:
//
void Game::updateEnemy(float fTime)
{
	glm::vec3 mPlayerPos = m_pPlayer->getPosition();

	for (unsigned int i = 0; i < v_vEnemy.size(); ++i)
	{
		glm::vec3 oldPosition = v_vEnemy[i].getPosition();

		v_vEnemy[i].updateDirection(glm::vec2(mPlayerPos.x, mPlayerPos.y));
		v_vEnemy[i].update(fTime);

		glm::vec3 newPosition = v_vEnemy[i].getPosition();

		if (collideEnemtToEnemy(newPosition, i))
		{
			v_vEnemy[i].setPosition(oldPosition);
		}
	}
}

//-----------------------------------------------
// Name:
// Desc:
//
void Game::updateShootGun(float fTime)
{
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

	GLuint uiTex = m_pBackground->getTexture();
	glBindTexture(GL_TEXTURE_2D, uiTex);
	glm::mat4 m_ObjectMatrix = m_pBackground->getWorld();
	m_ObjectMatrix = m_m4View * m_ObjectMatrix;
	m_pShader->set(m_ObjectMatrix);
	m_pBackground->getDraw()->render();


	glEnable(GL_BLEND);

	uiTex = m_pPlayer->getTexture();
	glBindTexture(GL_TEXTURE_2D, uiTex);
	m_ObjectMatrix = m_pPlayer->getWorld();
	m_ObjectMatrix = m_m4View * m_ObjectMatrix;
	m_pShader->set(m_ObjectMatrix);
	m_pPlayer->getDraw()->render();


	for (unsigned int i = 0; i < v_vEnemy.size(); ++i)
	{
		if (uiTex != v_vEnemy[i].getTexture())
		{
			uiTex = v_vEnemy[i].getTexture();
		}
		glBindTexture(GL_TEXTURE_2D, uiTex);
		m_ObjectMatrix = v_vEnemy[i].getWorld();
		m_ObjectMatrix = m_m4View * m_ObjectMatrix;
		m_pShader->set(m_ObjectMatrix);
		v_vEnemy[i].getDraw()->render();
	}

	for (unsigned int i = 0; i < v_vWeapon.size(); ++i)
	{
		if (uiTex != v_vWeapon[i].getTexture())
		{
			uiTex = v_vWeapon[i].getTexture();
		}
		glBindTexture(GL_TEXTURE_2D, uiTex);
		m_ObjectMatrix = v_vWeapon[i].getWorld();
		m_ObjectMatrix = m_m4View * m_ObjectMatrix;
		m_pShader->set(m_ObjectMatrix);
		v_vWeapon[i].getDraw()->render();
	}

	glDisable(GL_BLEND);

	m_pShader->Disable();

}