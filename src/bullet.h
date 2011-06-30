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
	B_REG,		// pos, vel, flies in straight line
	B_ACCEL,	// pos, vel, acc, accelerates along acc vector
	B_BOUNCE,	// pos, vel, acc, bounces when hits solid obsatcles
	B_WAVE,		// pos, direction, flies in a sin wave pattern
	B_CHASE,	// pos, vel, target, accelerates towards target
	B_BEAM,		// pos, direction, fires instant ray 
	B_LUA		// pos, vel, acc, checks with lua for instructions
};

typedef struct emitter {	
	pool pool;
	vec2d pos;
	int btype;	
	
	float direction;	
	float rate;
	float lin_speed;	
	float angular_speed;
	
	float direction_variance;
	float rate_variance;	
	float lin_speed_variance;
	float angular_speed_variance;

	GLuint tex_id;
} emitter;

typedef struct bullet {
	vec2d pos;
	vec2d vel;
	vec2d acc;
	
	int alive;
	int btype;
	
	vertex *vertex;
	GLuint tex_id;
} bullet;

emitter * emitter_new();
void emitter_destroy(emitter *e);
void emitter_update(emitter *e);
void emitter_emit(emitter *e);

void bullet_init(void *p);
void bullet_emit(bullet *b, vec2d p, vec2d v);
void bullet_update(bullet *b, float dt);
void bullet_kill(bullet *b);

#endif