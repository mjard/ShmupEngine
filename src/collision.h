//
//  collision.h
//  ShmupEngine
//

#ifndef COLLISION_H
#define COLLISION_H

#include <stdlib.h>
#include <stdio.h>

#include "entity.h"
#include "vector.h"

static inline int 
aabb_vs_aabb(vec2d a, vec2d a_size, vec2d b, vec2d b_size)
{
	if (a.x + a_size.x < b.x) return 0;
	if (b.x + b_size.x < a.x) return 0;
	if (a.y + a_size.y < b.y) return 0;
	if (b.y + b_size.y < a.y) return 0;
	return 1;
}

static inline int 
circle_vs_circle(vec2d a, double a_radius, vec2d b, double b_radius)
{
	if (v2lensq(v2sub(a, b)) > pow(a_radius + b_radius, 2)) return 0;
	return 1;
}

static inline int 
circle_vs_aabb(vec2d a, double a_radius, vec2d b, vec2d b_size)
{
	return 0;
}

static inline int 
point_vs_aabb(vec2d a, vec2d b, vec2d b_size)
{
	if (a.x < b.x) return 0;
	if (a.x > b.x + b_size.x) return 0;
	if (a.y < b.y) return 0;
	if (a.y > b.y + b_size.y) return 0;
	return 1;
}

static inline int point_vs_circle(vec2d a, vec2d b, double b_radius);

#endif