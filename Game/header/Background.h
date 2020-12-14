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
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "helper.h"
#include "Draw.h"

class Background
{

public:
	Background();
	~Background();

	void render();
	void update();
	void setPosition(glm::vec3 v3Pos);
	void init(glm::vec3 v3pos, GLuint uiTextureID, Draw *pDraw);

	void setTexture(GLuint uiTex);
	GLuint getTexture();
	glm::mat4 getWorld();

	Draw* getDraw() const;

private:
	
	glm::mat4 m_m4World;

	glm::vec3 m_v3Translate;
	glm::vec3 m_v3Rotate;
	glm::vec3 m_v3Scale;

	GLuint m_uiTextureID;

	Draw* m_pDraw;

	
};//background

#endif