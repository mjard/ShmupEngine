//
//  entity.c
//  ShmupEngine
//

#include "entity.h"

pool * 
pool_new(int size)
{
	int i;
	pool *p = malloc(sizeof(pool) + sizeof(pool_entity) * size);
	p->entity_list = (pool_entity*) p + 1;
	p->size = size;
	p->gravity = v2(0, -150);
	for (i=0; i < size; i++) {
		p->entity_list[i].pos = v2(400,300);
		p->entity_list[i].vel.x = ((float)rand()/RAND_MAX-0.5) * 400;
		p->entity_list[i].vel.y = ((float)rand()/RAND_MAX) * 400;
		p->entity_list[i].acc = p->gravity;
	}
	return p;
}

void 
pool_destroy(pool *p)
{
	free(p);
}

void 
pool_update(pool *p, double dt)
{
	int i;
	pool_entity* l = p->entity_list;
	for (i=0; i < p->size; i++) {
		l[i].pos = v2add(l[i].pos, v2mul(l[i].vel, dt));
		l[i].vel = v2add(l[i].vel, v2mul(l[i].acc, dt));
		if (l[i].pos.y < 0) {
			p->entity_list[i].pos = v2(400,300);
			p->entity_list[i].vel.x = ((float)rand()/RAND_MAX-0.5) * 400;
			p->entity_list[i].vel.y = ((float)rand()/RAND_MAX) * 400;
		}
	}
}

void 
pool_resize(pool *p, int size)
{
	
}

void 
pool_draw(pool *p)
{
	int i;
	pool_entity* l = p->entity_list;
	for (i=0; i < p->size; i++) {
		glVertex2f(l[i].pos.x, l[i].pos.y);
	}	
}