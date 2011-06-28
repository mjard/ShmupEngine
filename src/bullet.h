//
//  bullet.h
//  ShmupEngine
//

#ifndef BULLET_H
#define BULLET_H

#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "game.h"

typedef struct bullet {
	vec2d position;
	vec2d velocity;
	int alive;
} bullet;

bullet * bullet_new(vec2d p, vec2d v);
extern inline void bullet_update(bullet *b, float dt);
void bullet_explode(bullet *b);
void bullet_kill(bullet *b);
void bullet_destroy(bullet *b);

#endif