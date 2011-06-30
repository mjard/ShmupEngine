//
//  emitter.h
//  ShmupEngine
//

#ifndef EMITTER_H
#define EMITTER_H

#include "vector.h"
#include "GL/glfw.h"

typedef struct emitter {	
	//	bpool bpool;
	vec2d pos;
	int btype;	
	
	float direction;	
	float rate;
	float lin_speed;	
	float angular_speed;
	
	float direction_variance;
	float rate_variance;	
	float lin_speed_variance;
	float angular_speed_variance;
	
	GLuint tex_id;
} emitter;

emitter * emitter_new();
void emitter_destroy(emitter *e);
void emitter_update(emitter *e);
void emitter_emit(emitter *e);

#endif