//
//  game.h
//  ShmupEngine
//

#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>
#include "soil/SOIL.h"

#include "shader.h"
#include "bullet.h"
#include "vector.h"
#include "collision.h"

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#define MAX_BULLETS 200000

typedef struct shmup_game {
	int quit;
  int window_width;
  int window_height;
	bpool *bpool;
	vec2d emitter;
	vec2d gravity;	
	int render_type;
} shmup_game;

shmup_game * shmup_game_init();
void shmup_game_run(shmup_game *g);
void shmup_game_update(shmup_game *g, double t, double dt);
void shmup_game_draw(shmup_game *g);
void shmup_game_close(shmup_game *g);

#endif
