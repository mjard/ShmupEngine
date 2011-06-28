//
//  vector.h
//  ShmupEngine
//

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct vec2d {
	double x;
	double y;
} vec2d;

static const vec2d v2zero = {0.0, 0.0};

static inline vec2d
v2(const double x, const double y)
{
	vec2d v = {x, y};
	return v;
}

static inline vec2d 
v2add(const vec2d a, const vec2d b) 
{ 
	return v2(a.x + b.x, a.y + b.y); 
}

static inline vec2d 
v2sub(const vec2d a, const vec2d b) 
{ 
	return v2(a.x - b.x, a.y - b.y); 
}

static inline vec2d 
v2mul(const vec2d a, const double s) 
{ 
	return v2(a.x * s, a.y * s); 
}

static inline vec2d 
v2div(const vec2d a, const double s) 
{ 
	return v2(a.x / s, a.y / s); 
}

static inline double 
v2len(const vec2d v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

static inline double 
v2lensq(const vec2d v)
{
	return v.x * v.x + v.y * v.y;
}

static inline vec2d
v2normal(const vec2d v) {
	double l = v2len(v);
	return v2(v.x / l, v.y / l);
}

#endif