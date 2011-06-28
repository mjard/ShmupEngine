//
//  bullet.c
//  ShmupEngine
//

#include "bullet.h"

bullet *
bullet_new(vec2d p, vec2d v) 
{
	bullet *b = malloc(sizeof(bullet));
	if (b == NULL) {
		fprintf(stderr, "Failed to allocate bullet\n");
		return NULL;
	}
	b->position = p;
	b->velocity = v;
	b->alive = 1;
	return b;
}

void
bullet_explode(bullet *b)
{
	b->position = v2(400, 200);
	b->velocity = v2((float)rand() / RAND_MAX-0.5,(float)rand() / RAND_MAX);
	b->velocity = v2mul(v2normal(b->velocity), 200.0f);
	b->alive = 1;
}

void 
bullet_update(bullet *b, float dt)
{		
	if (!b->alive) return;
	b->position = v2add(b->position, v2mul(b->velocity, dt));
	b->velocity = v2add(b->velocity, v2mul(v2(0, -150.0f), dt));
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