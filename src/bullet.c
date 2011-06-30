 //
//  bullet.c
//  ShmupEngine
//

#include "bullet.h"

void
bullet_init(bullet *b, vertex *v)
{
	b->pos = v2zero;
	b->vel = v2zero;
	b->acc = v2zero;
	v->x = b->pos.x;
	v->y = b->pos.y;
}

void
bullet_emit(bullet *b, vertex *v, vec2d pos, vec2d vel, vec2d acc, unsigned int color) {
	b->pos = pos;
	b->vel = vel;
	b->acc = acc;
	v->x = b->pos.x;
	v->y = b->pos.y;
	v->color = color;	
}

void 
bullet_update(bullet *b, vertex *v, float dt)
{
	b->pos = v2add(b->pos, v2mul(b->vel, dt));	
	b->vel = v2add(b->vel, v2mul(b->acc, dt));	
	v->x = b->pos.x;
	v->y = b->pos.y;
}


/*
 * Create a new pool. Allocate space at the end of the pool struct to hold the
 * array of pool items.
 */

bpool * 
bpool_new(int size)
{	
	int i;
	bpool *bp = malloc(sizeof(bpool) + sizeof(vertex) * size + sizeof(bullet) * size);
	bp->size = size;
	bp->vdata = (vertex *)(bp + 1);
	bp->bdata = (bullet *)(bp->vdata + size);
	bp->n_active = 0;
	
	for (i=0; i < size; ++i)
		bullet_init(&bp->bdata[i], &bp->vdata[i]);
	
	return bp;
}

bpool * 
bpool_resize(bpool *bp, int size)
{
	if (size <= bp->size) 
		return bp;
	
	bpool *bp_new = bpool_new(size);
	bp_new->n_active = bp->n_active;
	memcpy(bp_new->vdata, bp->vdata, sizeof(vertex) * bp->size);
	memcpy(bp_new->bdata, bp->bdata, sizeof(bullet) * bp->size);
	bpool_destroy(bp);
	return bp_new;
}

void 
bpool_destroy(bpool *bp)
{
	free(bp);
}

int 
bpool_activate(bpool *bp)
{
	if (bp->n_active >= bp->size) {
		fprintf(stderr, "bpool overrun!\n");
		return -1;
	}
	bullet_init(&bp->bdata[bp->n_active], &bp->vdata[bp->n_active]);
	return bp->n_active++;
}

void 
bpool_deactivate(bpool *bp, int index)
{
	if (index >= bp->size || index < 0) {
		fprintf(stderr, "bpool underrun!");
		exit(EXIT_FAILURE);
	}
	bullet *b = bp->bdata;
	vertex *v = bp->vdata;
	memcpy(&b[index], &b[bp->n_active-1], sizeof(bullet));
	memcpy(&v[index], &v[bp->n_active-1], sizeof(vertex));
	bp->n_active--;
}