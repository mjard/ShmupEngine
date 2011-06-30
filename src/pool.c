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
pool_new(int size, int entity_size, void (*init_func)(void *))
{	
	int i;
	pool *p = malloc(sizeof(pool) + entity_size * size);
	p->size = size;	
	p->data = (p + 1);
	
	for (i=0; i < size*entity_size; i+=entity_size) 
		(*init_func)(&p->data[i]);
	
	return p;
}

pool * 
pool_resize(pool *p, int size, int entity_size, void (*init_func)(void *))
{
	if (size <= p->size) return p;
	pool *new = pool_new(size, entity_size, init_func);
	memcpy(new->data, p->data, size*entity_size);
	pool_destroy(p);
	return new;
}

void 
pool_destroy(pool *p)
{
	free(p);
}