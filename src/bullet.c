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
	b->rgba[0] = 255;
	b->rgba[1] = 255;
	b->rgba[2] = 255;
	b->rgba[3] = 255;	
}

void
bullet_emit(bullet *b, vec2d p, vec2d v) {
	b->pos = p;
	double speed = (float)rand()/RAND_MAX * 400;
	double angle = (float)rand()/RAND_MAX * M_PI * 2;
	b->vel.x = sin(angle) * speed;
	b->vel.y = cos(angle) * speed;
	b->acc = v2zero;
	b->alive = 1;
	
	float colorbase = (float)rand()/RAND_MAX * 0.5;
	b->rgba[0] = colorbase;
	b->rgba[1] = colorbase;
	b->rgba[2] = 0.5 + (float)rand()/RAND_MAX * 0.5;
	b->rgba[3] = 1.0;
}

void 
bullet_update(bullet *b, float dt)
{		
//	if (!b->alive) return;
	b->pos = v2add(b->pos, v2mul(b->vel, dt));
	b->vel = v2add(b->vel, v2mul(b->acc, dt));
}

void
bullet_kill(bullet *b)
{
	b->alive = 0;
}
