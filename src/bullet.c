/*
 *  bullet.c
 *  ShmupEngine
 */

#include "bullet.h"

void
bullet_init(bullet *b)
{
	unsigned char colorbase;
	
	b->pos = v2zero;
	b->vel = v2zero;
	b->acc = v2zero;
	
	colorbase = rand() % 128;
	b->color = colorbase;
	b->color += colorbase * 0x100;
	b->color += (colorbase + rand() % (256-colorbase)) * 0x10000;
	b->color += 0xFF000000;
}

void
bullet_emit(bullet *b, vec2d pos, vec2d vel, vec2d acc) {
	b->pos = pos;
	b->vel = vel;
	b->acc = acc;
}

void 
bullet_update(bullet *b, float dt)
{
	b->pos = v2add(b->pos, v2mul(b->vel, dt));	
	b->vel = v2add(b->vel, v2mul(b->acc, dt));	
}


/*
 * Create a new pool. Allocate space at the end of the pool struct to hold the
 * array of pool items.
 *
 * Bullet pools are maintained with all of the alive bullets at the front, and
 * all of the dead bullets at the end. => [AAAAAAAAAADDDD]
 * 
 * We do this so that whenever we need to iterate the bullet list, we can simply
 * just iterate pool->n_alive times and then stop and ignore the rest. n_alive 
 * is the variable that dictates which are alive and which are dead, based off 
 * of their position in the array.
 * 
 * This special ordering is very cheap to maintain. When we need a new bullet,
 * we just grab the one from bdata[n_alive] (This reprents the first dead one
 * in the list) and then increment n_alive.
 *
 * When we need to kill a bullet, we copy the bullet at bdata[n_alive-1] (this
 * represents the last alive one) over top of the one we want to kill. Then we
 * just decrement n_alive.
 */

bpool * 
bpool_new(int size)
{	
	int i, total;
	bpool *bp;
	
	total = sizeof(bpool) + sizeof(bullet) * size;
	bp = malloc(total);
	bp->size = size;
	bp->bdata = (bullet *)(bp + 1);
	bp->n_active = 0;
	
	for (i=0; i < size; ++i)
		bullet_init(&bp->bdata[i]);
	
	return bp;
}

bpool * 
bpool_resize(bpool *bp, int size)
{
	bpool *bp_new;
	
	if (size <= bp->size) {
		/* can't reduce size, YET! */
		return bp;
	}
		
	bp_new = bpool_new(size);
	bp_new->n_active = bp->n_active;
	bp_new->tex[0] = bp->tex[0];
	bp_new->tex[1] = bp->tex[1];
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
	return bp->n_active++;
}

void 
bpool_deactivate(bpool *bp, int index)
{	
	if (index >= bp->size || index < 0) {
		fprintf(stderr, "bpool underrun!");
		exit(EXIT_FAILURE);
	}
	bp->bdata[index] = bp->bdata[bp->n_active-1];
	bp->n_active--;
	
	//	bullet *b;
	//	b = bp->bdata;
	//	memcpy(&b[index], &b[bp->n_active-1], sizeof(bullet));
}