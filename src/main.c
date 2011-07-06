#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>

#include "game.h"

int
main(int argc, char **argv)
{
	shmup_game *g;
	
	if(!glfwInit()) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		exit(EXIT_FAILURE);
	}

	if(!glfwOpenWindow(WINDOW_WIDTH,WINDOW_HEIGHT,8,8,8,8,8,0,GLFW_WINDOW)){
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowTitle("ShmupEngine");
//	glfwSetWindowSizeCallback( resize );
	glfwSwapInterval(1);
	glfwSetMousePos(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	glfwEnable(GLFW_MOUSE_CURSOR);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, 100, -100);
	glMatrixMode(GL_MODELVIEW);
	
	g = shmup_game_init();
	
	g->network_type = CLIENT;
	for (int i=0; i<argc; ++i) {
		if (strcmp("-a", argv[i])) g->network_type = SERVER;
	}
		
	shmup_game_run(g);
	shmup_game_close(g);
	
	glfwTerminate();	
	exit(EXIT_SUCCESS);
}
