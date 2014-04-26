/* Bouncy bouncy elephant */
#include "fant.h"
#include "surface.h"


struct fant *fant_init(struct surface *s) {
	struct fant *f;

	f = malloc(sizeof(*f));
	f->sprite = d_sprite_load("res/fant.spr", 0, DARNIT_PFORMAT_RGB5A1);
	f->r = s->r / 2 + 64;
	f->angle = 0;

	return f;
}


void fant_move(struct surface *s, struct fant *f, int angle) {
	int x, y, sin, cos, x_o, y_o;

	angle *= -1;
	sin = d_util_sin(angle);
	cos = d_util_sin(angle + 900);
	x = - d_sprite_width(f->sprite) / 2 + f->r;
	y = - d_sprite_height(f->sprite) / 2 + f->r;
	x_o = cos * x - sin * y;
	y_o = sin * x + cos * y;
	x_o /= 65536;
	y_o /= 65536;

	x_o += s->r / 2;
	y_o += s->r / 2 + 32;

	d_sprite_rotate(f->sprite, (angle - 450) * -1);
	d_sprite_move(f->sprite, x_o, y_o);

	return;
}

void fant_draw(struct fant *f) {
	d_render_blend_enable();
	d_sprite_draw(f->sprite);
	d_render_blend_disable();

	return;
}


