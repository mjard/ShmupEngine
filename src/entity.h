//
//  entity.h
//  ShmupEngine
//

#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include "vector.h"
#include "GL/glfw.h"

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

entity * entity_new();
void entity_destroy(entity *e);
void entity_update(entity *e);
void entity_draw(entity *e);

#endif