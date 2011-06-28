//
//  game.h
//  ShmupEngine
//

#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>

#include "vector.h"
#include "list.h"
#include "bullet.h"

#define MAX_BULLETS 10000

typedef struct shmup_game {
	int quit;
	list *bullets;
} shmup_game;

shmup_game * shmup_game_init();
void shmup_game_run(shmup_game *g);
void shmup_game_update(shmup_game *g, double t, double dt);
void shmup_game_draw(shmup_game *g);
void shmup_game_close(shmup_game *g);

#endif