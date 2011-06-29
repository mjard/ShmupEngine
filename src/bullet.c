//
//  bullet.c
//  ShmupEngine
//

#include "bullet.h"

//bullet *
//bullet_new(vec2d p, vec2d v) 
//{
//	bullet *b = malloc(sizeof(bullet));
//	if (b == NULL) {
//		fprintf(stderr, "Failed to allocate bullet\n");
//		return NULL;
//	}
//	b->pos = p;
//	b->vel = v;
//	b->alive = 1;
//	return b;
//}

void
bullet_init(bullet *b, vec2d p, vec2d v)
{
	b->pos = p;
	b->vel.x = ((float)rand()/RAND_MAX-0.5) * 400;
	b->vel.y = ((float)rand()/RAND_MAX) * 400;
	b->acc = v2zero;
	b->alive = 1;
	
	float temp = (float)rand()/RAND_MAX * 0.5;
	b->rgba[0] = temp;
	b->rgba[1] = temp;
	b->rgba[2] = 0.5 + (float)rand()/RAND_MAX * 0.5;
	b->rgba[3] = 255;
}

void 
bullet_update(bullet *b, float dt)
{		
	if (!b->alive) return;
	b->pos = v2add(b->pos, v2mul(b->vel, dt));
	b->vel = v2add(b->vel, v2mul(b->acc, dt));
}

void
bullet_kill(bullet *b)
{
	b->alive = 0;
}

void
bullet_destroy(bullet *b)
{
	free(b);
}