//
//  game.c
//  ShmupEngine
//

#include "game.h"

shmup_game * 
shmup_game_init() 
{
	shmup_game *g = malloc(sizeof(shmup_game));	
	g->quit = 0;	
	g->emitter = v2(400,300);
	g->gravity = v2(0, -150);
	
	g->bpool = pool_new(MAX_BULLETS, sizeof(bullet), bullet_init);
	
	bullet *b = g->bpool->data;
	for (int i=0; i<g->bpool->size; i++) {
		bullet_emit(&b[i], g->emitter, v2zero);
		b[i].acc = g->gravity;
	}

	return g;
}

void
bullet_resize(shmup_game *g, int size)
{
	int old_size = g->bpool->size;
	g->bpool = pool_resize(g->bpool, size, sizeof(bullet), bullet_init);		
	bullet *b = g->bpool->data;
	for (int i=old_size-1; i<g->bpool->size; i++) {
		bullet_emit(&b[i], g->emitter, v2zero);
		b[i].acc = g->gravity;
	}
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
		g->emitter.y += 10;
	} else if (glfwGetKey(GLFW_KEY_DOWN)) {
		g->emitter.y -= 10;
	}
	
	if (glfwGetKey(GLFW_KEY_LEFT)) {
		g->emitter.x -= 10;
	} else if (glfwGetKey(GLFW_KEY_RIGHT)) {
		g->emitter.x += 10;
	}
		
	bullet *b = g->bpool->data;
	for (int i=0; i<g->bpool->size; i++) {
		bullet_update(&b[i], dt);
		if (b[i].pos.y < 0) {
			bullet_emit(&b[i], g->emitter, v2zero);
			b[i].acc = g->gravity;
		}
	}
	
	if (t > 4 && g->bpool->size == 10) bullet_resize(g, 100);
	if (t > 8 && g->bpool->size == 100) bullet_resize(g, 1000);
	if (t > 12 && g->bpool->size == 1000) bullet_resize(g, 10000);
	if (t > 16 && g->bpool->size == 10000) bullet_resize(g, 100000);
	
}

void shmup_game_draw(shmup_game *g) 
{   
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(2.0);
	glBegin(GL_POINTS);
	{
		bullet *b = g->bpool->data;
		for (int i=0; i<g->bpool->size; i++) {
			glColor4f(
				  b[i].rgba[0],
				  b[i].rgba[1],
				  b[i].rgba[2],
				  b[i].rgba[3]
			);
			glVertex2f(b[i].pos.x, b[i].pos.y);
		}
	}
	glEnd();
	glfwSwapBuffers();
}

void shmup_game_close(shmup_game *g) {
	pool_destroy(g->bpool);
	free(g);
}