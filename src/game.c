/*
 *  game.c
 *  ShmupEngine
 */

#include "game.h"

void fire(shmup_game *g, int num, int col);

shmup_game *
shmup_game_init()
{
	shmup_game *g = malloc(sizeof(shmup_game));	
	g->render_type = 1;
	g->quit = 0;	
	g->emitter = v2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	g->gravity = v2(0, -250);	
	g->bpool = bpool_new(4000);
			
	g->bpool->tex[0] = SOIL_load_OGL_texture("./data/flare.tga",
						 SOIL_LOAD_AUTO,
						 SOIL_CREATE_NEW_ID, 0);
	
	if(g->bpool->tex[0] == 0)
		fprintf(stderr, "loading error: '%s'\n", SOIL_last_result());
	
	g->bpool->tex[1] = SOIL_load_OGL_texture("./data/arrow.tga",
						 SOIL_LOAD_AUTO,
						 SOIL_CREATE_NEW_ID, 0);
	
	if(g->bpool->tex[1] == 0)
		fprintf(stderr, "loading error: '%s'\n", SOIL_last_result());	
	
	g->bpool->prog = load_shaders("./data/glsl/bullets.vsh", 
				      "./data/glsl/bullets.fsh");
	
	fire(g, 1000, 0);
	fire(g, 1000, 1);
	return g;
}

void 
shmup_game_run(shmup_game *g) 
{
	double t, current_time, accumulator;
	double new_time, frame_time;
	const double dt = 1.0f/60;

	t = 0.0;
	current_time = glfwGetTime();
	accumulator = 0.0;
	
	while (!g->quit) {
		
		new_time = glfwGetTime();
		frame_time = new_time - current_time;
		current_time = new_time;        
		accumulator += frame_time;
		
		while (accumulator >= dt) {
			shmup_game_update(g, t, dt);
			accumulator -= dt;
			t += dt;			
		}
		
		shmup_game_draw(g);
		
		g->quit = glfwGetKey(GLFW_KEY_ESC);
		g->quit |= !glfwGetWindowParam(GLFW_OPENED);			
	}
}

void
fire(shmup_game *g, int num, int col)
{
	bullet *b;
	unsigned int i, index;
	double angle, speed;
	vec2d vel;
	
	for (i=0; i<num; ++i) {
		index = bpool_activate(g->bpool);
		if (index == -1){
			/* we need to resize the pool */
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
		
		speed = 200.0 + (float)rand()/RAND_MAX * 400;
		angle = (float)rand()/RAND_MAX * M_PI * 2;
		vel = v2(cos(angle)*speed, sin(angle)*speed);
		
		if (col) {
			unsigned char colorbase;
			colorbase = rand() % 128;
			b->color = colorbase;
			b->color += colorbase * 0x100;
			b->color += (colorbase + rand() % (256-colorbase)) *
				0x10000;
			b->color += 0xFF000000;	
			b->btype = B_REG;
		} else {
			unsigned char colorbase;
			colorbase = rand() % 128;
			b->color = (colorbase + rand() % (256-colorbase));
			b->color += colorbase * 0x100;
			b->color += colorbase * 0x10000;
			b->color += 0xFF000000;
			b->btype = B_ACCEL;
		}
		
		bullet_emit(b, g->emitter, vel, g->gravity);		
	}
}

void 
shmup_game_update(shmup_game *g, double t, double dt)
{				
	
	{
		static int mx, my;
		glfwGetMousePos(&mx, &my);
		g->emitter.x = (double) mx;
		g->emitter.y = (double) 600-my;
	}
	
	if (glfwGetKey(GLFW_KEY_SPACE) || glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
		fire(g, 20, 0);
	} else if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)) {
		fire(g, 20, 1);
	}
	if (glfwGetKey('1')) g->render_type=1;
	if (glfwGetKey('2')) g->render_type=2;
	
	/* 
	 * be careful with these, as this data may be moved by the bpool_resize
	 * function!
	 */
	 
	bullet *b = g->bpool->bdata;
	
	/* Do updates */	
	for (int i=0; i < g->bpool->n_active; ++i) {
		bullet_update(&b[i], dt);
	}
	
	/* do collisions */
	for (int i=0; i < g->bpool->n_active; ++i) {
		
		if (b[i].pos.y > WINDOW_HEIGHT && b[i].vel.y > 0) {
			b[i].vel.y *= -0.6;
		} else if (b[i].pos.y < 0) {
			/* deactivate and rollback i to checked the swapped element */
			bpool_deactivate(g->bpool, i--); 
		}		
		if (b[i].pos.x < 0 && b[i].vel.x < 0 || b[i].pos.x > WINDOW_WIDTH && b[i].vel.x > 0) {
			b[i].vel.x *= -0.6;
		}		
	}	
}

/*
 * This function draws the current scene.
 */

void 
shmup_game_draw(shmup_game *g) 
{   	
	bullet *b = g->bpool->bdata;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_DEPTH_TEST);
//	glDepthFunc();
//	glDepthMask(GL_FALSE);
	
	glPointSize(16.0f);
	
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_TEXTURE_2D);
		
	if (g->render_type == 1) {		
		glBindTexture(GL_TEXTURE_2D, g->bpool->tex[0]);
		glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(2, GL_DOUBLE, sizeof(bullet), &b[0].pos);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(bullet), &b[0].color);
	} else {
		glBindTexture(GL_TEXTURE_2D, g->bpool->tex[1]);
		glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_FALSE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(4, GL_DOUBLE, sizeof(bullet), &b[0].pos);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(bullet), &b[0].color);
		glUseProgram(g->bpool->prog);
//		glUniform1iARB(glGetUniformLocation(g->bpool->prog, "tex"), 0);
	}
	
	glDrawArrays(GL_POINTS, 0, g->bpool->n_active);	
	glUseProgram(0);
	
	glfwSwapBuffers();
}

void shmup_game_close(shmup_game *g) {
	bpool_destroy(g->bpool);
	free(g);
}