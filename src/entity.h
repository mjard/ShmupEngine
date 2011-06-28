//
//  entity.h
//  ShmupEngine
//

#ifndef ENTITY_H
#define ENTITY_H

#include "vector.h"

enum COLLISION_SHAPE {
	CIRCLE = 1,
	AABB = 2
};

typedef struct entity {	
	vec2d pos;
	vec2d vel;
	vec2d acc;
	int shape;
	int radius;
} entity;

typedef struct pool_entity {
	vec2d pos;
	vec2d vel;
	vec2d acc;
} pool_entity;

typedef struct pool {
	int total_entities;
	int alive_entities;
	pool_entity *entity_list;
	vec2d gravity;
	int shape;
	int radius;
} pool;

entity * entity_new();
void entity_destroy(entity *e);
void entity_update(entity *e);
void entity_draw(entity *e);

pool * pool_new(int size);
void pool_destroy(pool *p);
void pool_update(pool *p);
void pool_resize(pool *p, int size);
void pool_draw(pool *p);

#endif