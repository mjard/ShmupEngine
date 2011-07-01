/*
 *  bullet.h
 *  ShmupEngine
 */

#ifndef BULLET_H
#define BULLET_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glfw.h>

#include "vector.h"

enum B_TYPE {
	B_REG,		// pos, vel, flies in straight line
	B_ACCEL,	// pos, vel, acc, accelerates along acc vector
	B_BOUNCE,	// pos, vel, acc, bounces when hits solid obsatcles
	B_WAVE,		// pos, direction, flies in a sin wave pattern
	B_CHASE,	// pos, vel, target, accelerates towards target
	B_BEAM,		// pos, direction, fires instant ray 
	B_LUA		// pos, vel, acc, checks with lua for instructions
};

typedef struct bullet {
	vec2d pos;
	vec2d vel;
	vec2d acc;
	unsigned int color;
	float padding[3];
} bullet;

typedef struct bpool {
	int size;
	int n_active;	
	GLuint tex;
	GLuint prog;
	bullet *bdata;
} bpool;

void bullet_init(bullet *b);
void bullet_emit(bullet *b, vec2d pos, vec2d vel, vec2d acc);
void bullet_update(bullet *b, float dt);

bpool * bpool_new(int size);
bpool * bpool_resize(bpool *bp, int size);
void bpool_destroy(bpool *bp);
int bpool_activate(bpool *bp);
void bpool_deactivate(bpool *bp, int index);

#endif