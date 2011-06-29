//
//  pool.h
//  ShmupEngine
//

#ifndef POOL_H
#define POOL_H

#include <stdlib.h>
#include "vector.h"

typedef struct pool {
	int size;
	int num_alive;
	vec2d gravity;
	void *data;
} pool;

pool * pool_new(int size, int entity_size);
void pool_destroy(pool *p);
void * pool_get_data(pool *p);
void pool_resize(pool *p, int size);

#endif