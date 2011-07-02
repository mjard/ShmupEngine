#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>

#include "game.h"

int
main(void)
{
	shmup_game *g;
	GLFWvidmode d_mode;    
	
	if(!glfwInit()){
		fprintf( stderr, "Failed to initialize GLFW\n" );
		exit( EXIT_FAILURE );
	}

	glfwGetDesktopMode(&d_mode);

	if(!glfwOpenWindow(d_mode.Width, d_mode.Height, d_mode.RedBits, 
	        d_mode.GreenBits, d_mode.BlueBits, 8, 8, 0, GLFW_FULLSCREEN)) {
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowTitle("ShmupEngine");
//	glfwSetWindowSizeCallback( resize );
	glfwSwapInterval(1);
	glfwSetMousePos(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	//glfwEnable(GLFW_MOUSE_CURSOR);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, 100, -100);
	glMatrixMode(GL_MODELVIEW);
	
	g = shmup_game_init();
	shmup_game_run(g);
	shmup_game_close(g);

	
	glfwTerminate();	
	exit(EXIT_SUCCESS);
}
