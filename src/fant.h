#ifndef __FANT_H__
#define	__FANT_H__

#include <darnit/darnit.h>
#include "surface.h"

#define	FANT_ACCELERATION		6400
#define	FANT_JUMP_VELOCITY		-2000

struct fant {
	DARNIT_SPRITE			*sprite;
	int				r;
	int				angle;
	int				d_angle;
	int				velocity;
}i;

struct fant *fant_init(struct surface *s);
void *fant_destroy(struct fant *f);
void fant_move(struct surface *s, struct fant *f, int angle);
void fant_draw(struct fant *f);


#endif
