//
//  player.h
//  ShmupEngine
//

#import "vector.h"

typedef struct player {
	vec2d pos;
	vec2d vel;
	vec2d acc;
} player;

void player_update(player *p, float dt);