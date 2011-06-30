//
//  game.h
//  ShmupEngine
//

#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>

#include "bullet.h"
#include "vector.h"

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#define MAX_BULLETS 200000

typedef struct shmup_game {
	int quit;
	bpool *bpool;
	vec2d emitter;
	vec2d gravity;
} shmup_game;

shmup_game * shmup_game_init();
void shmup_game_run(shmup_game *g);
void shmup_game_update(shmup_game *g, double t, double dt);
void shmup_game_draw(shmup_game *g);
void shmup_game_close(shmup_game *g);

#endif