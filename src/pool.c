//
//  pool.c
//  ShmupEngine
//

#include "pool.h"

/*
 * Create a new pool. Allocate space at the end of the pool struct to hold the
 * array of pool items.
 */

pool * 
pool_new(int size, int entity_size)
{
	pool *p = malloc(sizeof(pool) + entity_size * size);
	p->size = size;
	p->gravity = v2(0, -150);
	p->data = (p + 1);
	return p;
}

void 
pool_destroy(pool *p)
{
	free(p);
}

void 
pool_resize(pool *p, int size)
{
	
}