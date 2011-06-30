//
//  pool.h
//  ShmupEngine
//

#ifndef POOL_H
#define POOL_H

#include <stdlib.h>
#include <string.h>

#include "vector.h"

typedef struct vertex {
	float x, y;
	unsigned int color;
	float padding[1];
} vertex;

typedef struct pool {
	int size;
	int num_alive;
	void *data;
	vertex *vdata;
} pool;

pool * pool_new(int size, int entity_size, void (*init_func)(void *));
pool * pool_resize(pool *p, int size, int entity_size, void (*init_func)(void *));
void pool_do(pool *p, void (*func)(void *));
void pool_destroy(pool *p);

#endif