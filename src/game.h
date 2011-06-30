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
#include "pool.h"
#include "vector.h"

#define MAX_BULLETS 10

typedef struct shmup_game {
	int quit;
	pool *bpool;
	vec2d emitter;
	vec2d gravity;
} shmup_game;

shmup_game * shmup_game_init();
void shmup_game_run(shmup_game *g);
void shmup_game_update(shmup_game *g, double t, double dt);
void shmup_game_draw(shmup_game *g);
void shmup_game_close(shmup_game *g);

#endif