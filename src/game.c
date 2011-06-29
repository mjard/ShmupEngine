//
//  game.c
//  ShmupEngine
//

#include "game.h"

shmup_game * 
shmup_game_init() 
{
	
	shmup_game *g = malloc(sizeof(shmup_game));
	srand(100);	
	g->quit = 0;
	g->bullet_pool = pool_new(MAX_BULLETS);
	return g;
}

void 
shmup_game_run(shmup_game *g) 
{
	double t = 0.0;
	const double dt = 1.0f/30;
	double currentTime = glfwGetTime();
	double accumulator = 0.0;
	
	while (!g->quit) 
	{
		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;        
		accumulator += frameTime;
		
		while (accumulator >= dt)
		{
			shmup_game_update(g, t, dt);
			accumulator -= dt;
			t += dt;			
		}
		
		shmup_game_draw(g);
		if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED)) 
			g->quit = 1;
	}
}

void 
shmup_game_update(shmup_game *g, double t, double dt)
{				
	pool_update(g->bullet_pool, dt);
}

void shmup_game_draw(shmup_game *g) 
{   
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// glTranslatef(b->position.x, b->position.y, 0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	{
		pool_draw(g->bullet_pool);
	}
	glEnd();
	glfwSwapBuffers();
}

void shmup_game_close(shmup_game *g) {
	pool_destroy(g->bullet_pool);
	free(g);
}