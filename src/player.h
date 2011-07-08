//
//  player.h
//  ShmupEngine
//
#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glfw.h>

#include "vector.h"
#include "common.h"
#include "game.h"

#define HALFSQRT2 0.707106781186548
#define PLAYER_ACC 3000
#define PLAYER_SPEED 300
#define PLAYER_D_SPEED PLAYER_SPEED * HALFSQRT2
#define PLAYER_SPEED_SQ PLAYER_SPEED * PLAYER_SPEED
#define PLAYER_D_ACC PLAYER_ACC * HALFSQRT2
#define BULLET_SPEED 2000

void player_update(shmup_game *g, player *p, float dt);
void player_fire(player *p);

#endif