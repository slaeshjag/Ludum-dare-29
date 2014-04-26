#ifndef __FANT_H__
#define	__FANT_H__

#include <darnit/darnit.h>
#include "surface.h"


struct fant {
	DARNIT_SPRITE			*sprite;
	int				r;
	int				angle;
}i;

struct fant *fant_init(struct surface *s);
void fant_move(struct surface *s, struct fant *f, int angle);
void fant_draw(struct fant *f);


#endif
