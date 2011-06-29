#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>

#include "game.h"

int
main(void)
{
	shmup_game *g;
	
	if(!glfwInit()){
		fprintf( stderr, "Failed to initialize GLFW\n" );
		exit( EXIT_FAILURE );
	}

	if(!glfwOpenWindow(800, 600, 5, 6, 5, 0, 8, 0, GLFW_WINDOW)) {
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowTitle("ShmupEngine");
//	glfwSetWindowSizeCallback( resize );
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	glOrtho(0, 800, 0, 600, 100, -100);
	glMatrixMode(GL_MODELVIEW);
	
	g = shmup_game_init();
	shmup_game_run(g);
	shmup_game_close(g);

	
	glfwTerminate();	
	exit(EXIT_SUCCESS);
}
