//
//  game.c
//  ShmupEngine
//

#include "game.h"

shmup_game * 
shmup_game_init() 
{
	int i;
	shmup_game *g = malloc(sizeof(shmup_game));
	srand(100);	
	g->quit = 0;
	g->bullet_pool = pool_new(MAX_BULLETS, sizeof(bullet));
	
	bullet* b = g->bullet_pool->data;
	for (i=0; i<g->bullet_pool->size; i++) {
		bullet_init(&b[i]);
		b[i].acc = g->bullet_pool->gravity;
	}

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

	if (glfwGetKey(GLFW_KEY_UP)) {
		
	} else if (glfwGetKey(GLFW_KEY_DOWN)) {
		
	}
	
	if (glfwGetKey(GLFW_KEY_LEFT)) {
		
	} else if (glfwGetKey(GLFW_KEY_RIGHT)) {
		
	}
	
	
	int i;
	bullet* b = g->bullet_pool->data;
	for (i=0; i<g->bullet_pool->size; i++) {
		bullet_update(&b[i], dt);
		if (b[i].pos.y < 0) {
			bullet_init(&b[i]);		
			b[i].acc = g->bullet_pool->gravity;	
		}
	}
}

void shmup_game_draw(shmup_game *g) 
{   
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// glTranslatef(b->pos.x, b->pos.y, 0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	{
		int i;
		bullet* b = g->bullet_pool->data;
		for (i=0; i < g->bullet_pool->size; i++) {			
			glColor4f(b[i].rgba[0],b[i].rgba[1],b[i].rgba[2],1.0);
			glVertex2f(b[i].pos.x, b[i].pos.y);
		}
	}
	glEnd();
	glfwSwapBuffers();
}

void shmup_game_close(shmup_game *g) {
	pool_destroy(g->bullet_pool);
	free(g);
}