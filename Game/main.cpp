#define MAX_NUM_MODES 400

#include <cstdlib>
#include "stdio.h"
#include "..\header\Game.h"
#include <algorithm>


int windowWidth = 1280;
int windowHeight = 720;


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


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main()
{

	// GLFWvidmode dtmode, modes[ MAX_NUM_MODES ];
	 //int     modecount , i;

	 // Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	//GLFWmonitor* pMonitor;
	// Show desktop video mode
	//glfwGetVideoModes( &dtmode );
	//printf( "Desktop mode: %d x %d x %d\n\n",
	//        dtmode.Width, dtmode.Height, dtmode.RedBits +
	//        dtmode.GreenBits + dtmode.BlueBits );

	// List available video modes
	//modecount = glfwGetVideoModes( modes, MAX_NUM_MODES );
	//printf( "Available modes:\n" );
	//for( i = 0; i < modecount; i ++ )
   // {
	//        printf( "%3d: %d x %d x %d\n", i,
	//                modes[i].Width, modes[i].Height, modes[i].RedBits +
	//                modes[i].GreenBits + modes[i].BlueBits );
	//}

	GLFWwindow* window;

	window = glfwCreateWindow(windowWidth, windowHeight, "My Title", NULL, NULL);


	if (!window)
	{
		fprintf(stderr, "ERROR: Unable to create the OpenGL context and associated window\n");

		glfwTerminate();
		exit(EXIT_FAILURE);

	}

	glfwMakeContextCurrent(window);


	//printf("OpenGL Context: %d.%d\n", glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR), glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR));


	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	if (glewIsSupported("GL_VERSION_3_3"))
	{
		printf("all ok \n\n");
	}

	// glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	// glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	// glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	// glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_FORWARD_COMPAT);

	glfwSetKeyCallback(window, key_callback);

	//OpenGL init
	initOpenGL();

	glfwSwapInterval(1);

	Game* pGame = new Game();
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

		//running =  !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam(GLFW_OPENED);
		running = !glfwGetKey(window, GLFW_KEY_ESCAPE) && !glfwWindowShouldClose(window);
	}

	SAFE_DELETE(pGame);

	glfwTerminate();

	return 0;
}