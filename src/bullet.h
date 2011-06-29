//
//  bullet.h
//  ShmupEngine
//

#ifndef BULLET_H
#define BULLET_H

#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "pool.h"
#include "entity.h"
#include "vector.h"

enum B_TYPE {
	B_REG = 1,	// initial pos, vel, flies in straight line
	B_ACCEL = 2,	// initial pos, vel, acc, accelerates along acc vector
	B_BOUNCE = 3,	// initial pos, vel, acc, bounces when hits solid obsatcles
	B_WAVE = 4,	// initial pos, direction, flies in a sin wave pattern
	B_CHASE = 5,	// initial pos, vel, target, accelerates towards target
	B_BEAM = 6,	// initial pos, direction, fires instant ray 
	B_LUA = 7	// initial pos, vel, acc, checks with lua for instructions
};

typedef struct emitter {
	pool pool;
	entity entity;
	int btype;
	float direction;
	float direction_variance;
	float rate;
	float rate_variance;
	float lin_speed;
	float lin_speed_variance;
	float angular_speed;
	float angular_speed_variance;
} emitter;

typedef struct bullet {
	vec2d pos;
	vec2d vel;
	vec2d acc;
	int alive;
	int btype;
	GLfloat rgba[4];
} bullet;

emitter * emitter_new();
void emitter_destroy(emitter *e);
void emitter_update(emitter *e);
void emitter_emit(emitter *e);

//bullet * bullet_new(vec2d p, vec2d v);
void bullet_init(bullet *b);
void bullet_update(bullet *b, float dt);
void bullet_kill(bullet *b);
void bullet_destroy(bullet *b);

#endif