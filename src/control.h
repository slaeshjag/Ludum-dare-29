#ifndef __CONTROL_H__
#define	__CONTROL_H__

#include "surface.h"
#include "fant.h"
#include "trampoline.h"

#include <darnit/darnit.h>

struct control {
	int			angle;
	int			score;
	DARNIT_TEXT_SURFACE	*a_vel;
};

struct control *control_init();
void control_loop(struct surface *s, struct trampoline *t, struct fant *f, struct control *c);



#endif
