//
//  bullet.c
//  ShmupEngine
//

#include "bullet.h"

void
bullet_init(void *p)
{
	bullet *b = p;
	b->pos = v2(400,300);
	b->vel = v2zero;
	b->acc = v2(0,-150);
	b->alive = 0;
	b->btype = B_REG;
}

void
bullet_emit(bullet *b, vec2d p, vec2d v) {
	b->pos = p;
	b->vertex->x = b->pos.x;
	b->vertex->y = b->pos.y;
	double speed = (float)rand()/RAND_MAX * 400;
	double angle = (float)rand()/RAND_MAX * M_PI * 2;
	b->vel.x = sin(angle) * speed;
	b->vel.y = cos(angle) * speed;
	b->acc = v2zero;
	b->alive = 1;
	
	GLubyte colorbase = rand() % 128;
	b->vertex->color = colorbase;
	b->vertex->color += colorbase * 0x100;
	b->vertex->color += (colorbase + rand() % (256-colorbase)) * 0x10000;
	b->vertex->color += 0xFF000000;
	
}

void 
bullet_update(bullet *b, float dt)
{		
//	if (!b->alive) return;
	b->pos = v2add(b->pos, v2mul(b->vel, dt));	
	b->vel = v2add(b->vel, v2mul(b->acc, dt));	
	b->vertex->x = b->pos.x;
	b->vertex->y = b->pos.y;
}

void
bullet_kill(bullet *b)
{
	b->alive = 0;
}
