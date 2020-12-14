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
#define MAX_NUM_MODES 400

#include <cstdlib>
#include "stdio.h"
#include "Game.h"
#include <algorithm>


int windowWidth = 1280;
int windowHeight = 720;

//-----------------------------------------------
// Name:
// Desc:
//
void initOpenGL()
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//-----------------------------------------------
// Name:
// Desc:
//
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

//-----------------------------------------------
// Name:
// Desc:
//
int main()
{

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window;

	window = glfwCreateWindow(windowWidth, windowHeight, "Top 2D Game", NULL, NULL);


	if (!window)
	{
		fprintf(stderr, "ERROR: Unable to create the OpenGL context and associated window\n");

		glfwTerminate();
		exit(EXIT_FAILURE);

	}

	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	if (glewIsSupported("GL_VERSION_3_3"))
	{
		printf("all ok \n\n");
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_FORWARD_COMPAT);

	glfwSetKeyCallback(window, key_callback);

	initOpenGL();

	glfwSwapInterval(1);

	Game* pGame = NULL;
	pGame = new Game();


	if (!pGame)
	{
		glfwTerminate();
		return 0;
	}
	
	pGame->init(window, glm::vec2(windowWidth, windowHeight));

	bool running = true;

	glViewport(0, 0, windowWidth, windowHeight);

	double prev_time = 0.0, max_time_step = 0.2;

	while (running)
	{
		double fTime = glfwGetTime(),
			dtime = std::min(fTime - prev_time, max_time_step);
		prev_time = fTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pGame->update((float)dtime);
		pGame->render();

		glfwSwapBuffers(window);

		glfwPollEvents();

		running = !glfwGetKey(window, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(window);
	}

	SAFE_DELETE(pGame);

	glfwTerminate();

	return 0;
}