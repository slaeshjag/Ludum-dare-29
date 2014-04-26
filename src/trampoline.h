#ifndef __TRAMPOLINE_H__
#define	__TRAMPOLINE_H__

#include <darnit/darnit.h>
#include "surface.h"

struct trampoline {
	DARNIT_SPRITE			*sprite;
	int				angle;
};

struct trampoline *trampoline_init(struct surface *s);
void trampoline_move(struct surface *s, struct trampoline *t, int deg);
void trampoline_draw(struct trampoline *t);


#endif
