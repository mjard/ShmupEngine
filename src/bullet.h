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
} bullet;

typedef struct vertex {
	float x, y;
	float vx, vy;
	unsigned int color;
	float padding[3];
} vertex;

typedef struct bpool {
	int size;
	int n_active;
	bullet *bdata;
	vertex *vdata;
	GLuint tex;
	GLuint prog;
} bpool;

void bullet_init(bullet *b, vertex *v);
void bullet_emit(bullet *b, vertex *v, vec2d pos, vec2d vel, vec2d acc);
void bullet_update(bullet *b, vertex *v, float dt);

bpool * bpool_new(int size);
bpool * bpool_resize(bpool *bp, int size);
void bpool_destroy(bpool *bp);
int bpool_activate(bpool *bp);
void bpool_deactivate(bpool *bp, int index);

#endif