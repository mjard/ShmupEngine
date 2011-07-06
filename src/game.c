/*
 *  game.c
 *  ShmupEngine
 */

#include "game.h"

shmup_game *
shmup_game_init()
{
	ENetAddress e;
	shmup_game *g;
	
	g = malloc(sizeof(shmup_game));
	g->render_type = 1;
	g->quit = 0;	
	g->emitter = v2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	g->gravity = v2(0, -250);	
	g->bpool = bpool_new(2000);	
	
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
	
	if (enet_initialize () != 0) {
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		exit(EXIT_FAILURE);
	}
	
	if (g->network_type == SERVER) {
		e.host = ENET_HOST_ANY;
		e.port = 4000;
		g->host = enet_host_create(&e, 4, 2, 0, 0);
	} else {
		g->host = enet_host_create(NULL, 4, 2, 0, 0);
	}
	
	g->player[0].pos = v2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	g->player[0].vel = v2zero;
	g->player[0].acc = v2zero;
	
//	fire(g, 1000, 0);
//	fire(g, 1000, 1);
	
	return g;
}

void 
shmup_game_close(shmup_game *g) 
{
	bpool_destroy(g->bpool);
	free(g);
	enet_host_destroy(g->host);
	enet_deinitialize();
}

void 
shmup_game_run(shmup_game *g) 
{
	double accumulator, current_time, t;
	double frame_time, new_time;
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
shmup_game_fire(shmup_game *g, int num, int col)
{
	bullet *b;
	vec2d vel;
	unsigned int i, index;
	double angle, speed;
		
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
	
	bullet *b;
	static int mx, my;
	
	glfwGetMousePos(&mx, &my);
	g->emitter.x = (double) mx;
	g->emitter.y = (double) WINDOW_HEIGHT - my;	
	
	if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT))
		shmup_game_fire(g, 40, 0);
	
	if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT))
		shmup_game_fire(g, 40, 1);
	
	if (glfwGetKey('1')) 
		g->render_type=1;
	
	if (glfwGetKey('2')) 
		g->render_type=2;
	
	player *p = &g->player[0];
	if (glfwGetKey(GLFW_KEY_LEFT))
		if (glfwGetKey(GLFW_KEY_UP))
			p->vel = v2(-PLAYER_D_SPEED, PLAYER_D_SPEED);
		else if (glfwGetKey(GLFW_KEY_DOWN))
			p->vel = v2(-PLAYER_D_SPEED, -PLAYER_D_SPEED);
		else
			p->vel = v2(-PLAYER_SPEED, 0);
	
	else if (glfwGetKey(GLFW_KEY_RIGHT))
		if (glfwGetKey(GLFW_KEY_UP))
			p->vel = v2(PLAYER_D_SPEED, PLAYER_D_SPEED);
		else if (glfwGetKey(GLFW_KEY_DOWN))
			p->vel = v2(PLAYER_D_SPEED, -PLAYER_D_SPEED);
		else
			p->vel = v2(PLAYER_SPEED, 0);
	
	else
		if (glfwGetKey(GLFW_KEY_UP))
			p->vel = v2(0, PLAYER_SPEED);
		else if (glfwGetKey(GLFW_KEY_DOWN))
			p->vel = v2(0, -PLAYER_SPEED);
		else
			p->vel = v2zero;
	
	
	player_update(&g->player[0], dt);
	/* 
	 * be careful with this pointer, as this data may be moved by the 
	 * bpool_resize function! Make sure it points to the right place.
	 */
	 
	b = g->bpool->bdata;
	
	/* do updates */
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
	glDisable(GL_DEPTH_TEST);	
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_TEXTURE_2D);
//	glPushMatrix();
//	glDisable(GL_BLEND);	
	glTranslated(g->player[0].pos.x, g->player[0].pos.y, 0);	
	glBegin(GL_QUADS);
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex2d(-30, -10);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex2d(30, -10);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex2d(30, 10);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glVertex2d(-30, 10);
	}
	glEnd();
//	glPopMatrix();
	glLoadIdentity();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

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
