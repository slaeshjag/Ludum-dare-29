#include "trampoline.h"
#include "surface.h"
#include <stdlib.h>

struct trampoline *trampoline_init(struct surface *s) {
	struct trampoline *t;

	t = malloc(sizeof(*t));
	t->sprite = d_sprite_load("res/trampoline.spr", 0, DARNIT_PFORMAT_RGB5A1);
	t->angle = 0;
	d_sprite_move(t->sprite, -d_sprite_width(t->sprite) / 2 + s->r / 2, -d_sprite_height(t->sprite));

	return t;
}


void *trampoline_destroy(struct trampoline *t) {
	if (!t)
		return NULL;
	d_sprite_free(t->sprite);
	free(t);
	return NULL;
}


void trampoline_draw(struct trampoline *t) {
	d_render_blend_enable();
	d_sprite_draw(t->sprite);
	d_render_blend_disable();

	return;
}
