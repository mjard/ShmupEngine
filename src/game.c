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
	g->bullets = list_new();
		
	return g;
}

void 
shmup_game_run(shmup_game *g) 
{
	double t = 0.0;
	const double dt = 1.0f/30;
	double currentTime = glfwGetTime();
	double accumulator = 0.0;
	
	while ( !g->quit )
	{
		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;        
		accumulator += frameTime;
		
		while ( accumulator >= dt )
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
	list_node *node = g->bullets->head;	
	
	if (g->bullets->size < MAX_BULLETS) {
		bullet *b;
		for (int i = 0; i < 10; i++) {
			b = bullet_new(v2(400, 200), v2(0,0));
			if (b == NULL) continue;		
			bullet_explode(b);
			list_insert(g->bullets, b);
		}
	}
	
	while (node != NULL) {
		bullet *b = node->data;
		if (b->alive) {
			bullet_update(b, dt);			
			if (b->position.y < 0) {
//				list_remove(g->bullets, node);
				bullet_kill(b);
				bullet_explode(b);
			}
		}
		
		node = node->next;
	}
	
}

void shmup_game_draw(shmup_game *g) 
{   
	list_node *node = g->bullets->head;
	bullet *b = NULL;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// glTranslatef(b->position.x, b->position.y, 0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	{
		while (node != NULL) {
			b = node->data;
			glVertex2f(b->position.x, b->position.y);
			node = node->next;
		}
	}
	glEnd();
	glfwSwapBuffers();
}

void shmup_game_close(shmup_game *g) {
	list_node *node = g->bullets->head;
	bullet *b = NULL;
	while (node != NULL) {
		b = node->data;
		bullet_destroy(b);
		node = node->next;
	}
	list_destroy(g->bullets, 1);
	free(g);
}