//
//  player.c
//  ShmupEngine
//

#include "player.h"

void 
player_update(player *p, float dt)
{
	p->pos = v2add(p->pos, v2mul(p->vel, dt));	
	p->vel = v2add(p->vel, v2mul(p->acc, dt));
}