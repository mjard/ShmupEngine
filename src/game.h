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
#include <enet/enet.h>

#include "shader.h"
#include "bullet.h"
#include "player.h"
#include "vector.h"
#include "collision.h"

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#define HALFSQRT2 0.707106781186548

#define MAX_BULLETS 200000
#define WINDOW_WIDTH 1152
#define WINDOW_HEIGHT 720
#define PLAYER_SPEED 200
#define PLAYER_D_SPEED PLAYER_SPEED * HALFSQRT2

enum NETWORK_TYPE {
	CLIENT,
	SERVER
};

typedef struct shmup_game {
	int quit;
	int render_type;
	int network_type;
	vec2d emitter;
	vec2d gravity;
	player player[4];
	bpool *bpool;
	ENetHost *host;
} shmup_game;

shmup_game * shmup_game_init();
void shmup_game_run(shmup_game *g);
void shmup_game_update(shmup_game *g, double t, double dt);
void shmup_game_draw(shmup_game *g);
void shmup_game_close(shmup_game *g);
void shmup_game_fire(shmup_game *g, int num, int col);

#endif