//
//  player.c
//  ShmupEngine
//

#include "player.h"

void 
player_update(shmup_game *g, player *p, float dt)
{

	if (glfwGetKey(GLFW_KEY_LEFT))
		if (glfwGetKey(GLFW_KEY_UP))
			p->acc = v2(-PLAYER_D_ACC, PLAYER_D_ACC);
		else if (glfwGetKey(GLFW_KEY_DOWN))
			p->acc = v2(-PLAYER_D_ACC, -PLAYER_D_ACC);
		else
			p->acc = v2(-PLAYER_ACC, 0);
	
		else if (glfwGetKey(GLFW_KEY_RIGHT))
			if (glfwGetKey(GLFW_KEY_UP))
				p->acc = v2(PLAYER_D_ACC, PLAYER_D_ACC);
			else if (glfwGetKey(GLFW_KEY_DOWN))
				p->acc = v2(PLAYER_D_ACC, -PLAYER_D_ACC);
			else
				p->acc = v2(PLAYER_ACC, 0);
	
			else
				if (glfwGetKey(GLFW_KEY_UP))
					p->acc = v2(0, PLAYER_ACC);
				else if (glfwGetKey(GLFW_KEY_DOWN))
					p->acc = v2(0, -PLAYER_ACC);
				else {
					p->acc = v2zero;
					p->vel = v2mul(p->vel, 0.5);
				}
	
	if (glfwGetKey(GLFW_KEY_SPACE)) {
		shmup_game_fire(g, 1, 1, v2add(p->pos, v2(20, -10)), 
				v2(BULLET_SPEED,0), v2zero);
		shmup_game_fire(g, 1, 1, v2add(p->pos, v2(20, 10)), 
				v2(BULLET_SPEED,0), v2zero);
	}
		
	p->pos = v2add(p->pos, v2mul(p->vel, dt));	
	p->vel = v2add(p->vel, v2mul(p->acc, dt));
	if (v2lensq(p->vel) > PLAYER_SPEED_SQ) {
		p->vel = v2mul(v2normal(p->vel), PLAYER_SPEED);
	}
}