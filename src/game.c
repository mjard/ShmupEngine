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
	g->bpool = bpool_new(1000);

	return g;
}

void 
shmup_game_run(shmup_game *g) 
{
	double t = 0.0;
	const double dt = 1.0f/100;
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
fire(shmup_game *g, int num)
{
	bullet *b;
	vertex *v;
	unsigned int i, index, color;
	double angle, speed;
	vec2d vel;
	GLubyte colorbase;
	
	for (i=0; i<num; ++i) {
		index = bpool_activate(g->bpool);
		if (index == -1){
			int new_size = g->bpool->size * 2;
			fprintf(stderr, "resizing to %d!\n", new_size);
			g->bpool = bpool_resize(g->bpool, new_size);
			index = bpool_activate(g->bpool);
			if (index == -1) {
				fprintf(stderr, "FAILED!\n");
				exit(EXIT_FAILURE);
			}
		}
		
		b = &g->bpool->bdata[index];
		v = &g->bpool->vdata[index];
		
		speed = (float)rand()/RAND_MAX * 400;
		angle = (float)rand()/RAND_MAX * M_PI ;
		vel = v2(cos(angle)*speed, sin(angle)*speed);
		
		colorbase = rand() % 128;
		color = colorbase;
		color += colorbase * 0x100;
		color += (colorbase + rand() % (256-colorbase)) * 0x10000;
		color += 0xFF000000;	
		    
		bullet_emit(b, v, g->emitter, vel, g->gravity, color);		
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
	
	if (glfwGetKey(GLFW_KEY_SPACE)) {

		fire(g, 10);
		printf("%d/%d\n", g->bpool->n_active, g->bpool->size);
	}
	
	
	/* Do updates */
	bullet *b = g->bpool->bdata;
	vertex *v = g->bpool->vdata;		
	for (int i=0; i < g->bpool->n_active; ++i) {
		bullet_update(&b[i], &v[i], dt);
	}
	
	/* do collisions */
	for (int i=0; i < g->bpool->n_active; ++i) {
		if (b[i].pos.y < 0) {
			bpool_deactivate(g->bpool, i);
			i--; /* rollback the counter so that we can check the swapped element */
			printf("%d/%d\n", g->bpool->n_active, g->bpool->size);
		}
	}	
		
//	if (t > 4 && g->bpool->size == 10) g->bpool = bpool_resize(g->bpool, 100);
//	if (t > 8 && g->bpool->size == 100) g->bpool = bpool_resize(g->bpool, 1000);
//	if (t > 12 && g->bpool->size == 1000) g->bpool = bpool_resize(g->bpool, 10000);
//	if (t > 16 && g->bpool->size == 10000) g->bpool = bpool_resize(g->bpool, 100000);
	
}

void shmup_game_draw(shmup_game *g) 
{   	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(4.0);	
	vertex *v = g->bpool->vdata;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(vertex), &v[0].x);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(vertex), &v[0].color);
	glDrawArrays(GL_POINTS, 0, g->bpool->n_active);
	glfwSwapBuffers();
}

void shmup_game_close(shmup_game *g) {
	bpool_destroy(g->bpool);
	free(g);
}