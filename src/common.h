#ifndef COMMON_H
#define COMMON_H

#include <enet/enet.h>
#include "vector.h"

typedef struct bullet {
	vec2d pos;
	vec2d vel;
	vec2d acc;
	unsigned int color;
	unsigned int btype;
	float padding[2];
} bullet;

typedef struct bpool {
	int size;
	int n_active;	
	GLuint tex[2];
	GLuint prog;
	bullet *bdata;
} bpool;

typedef struct player {
	vec2d pos;
	vec2d vel;
	vec2d acc;
} player;

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



#endif