/* Bouncy bouncy elephant */
#include "fant.h"
#include "fanten.h"
#include "surface.h"

#define	ABS(x)		((x) < 0 ? (-x) : (x))

struct fant *fant_init(struct surface *s) {
	struct fant *f;

	f = malloc(sizeof(*f));
	f->sprite = d_sprite_load("res/fant.spr", 0, DARNIT_PFORMAT_RGB5A1);
	f->r = s->r / 2 + 64;
	f->angle = 0;
	f->d_angle = 0;
	f->velocity = 0;

	return f;
}


void *fant_destroy(struct fant *f) {
	if (!f)
		return NULL;
	d_sprite_free(f->sprite);
	free(f);
	return f;
}


int fant_sign_diff(int a, int b) {
	if (a < 0 && b > 0)
		return 1;
	if (a > 0 && b < 0)
		return 1;
	return 0;
}


void fant_move(struct surface *s, struct fant *f, int angle) {
	int x, y, sin, cos, x_o, y_o;
	angle = f->angle - angle;

	/* Handle height over surface */
	f->velocity += d_last_frame_time() * FANT_ACCELERATION / 1000;
	f->r -= f->velocity * d_last_frame_time() / 1000;
	if (f->r <= s->r / 2) {	/* This is where we should check for trampoline hit */
		surface_impact(s, ((s->angle - f->angle) % 3600));

		if (ABS(angle) > 0 && ABS(angle) && ABS(angle) < 100) {
			if (fant_sign_diff(angle, f->d_angle) && ABS(f->d_angle) > 2 * ABS(angle))
				f->d_angle += 2 * angle;
			else
				f->d_angle += angle;
		} else if (angle) {
			fprintf(stderr, "DEAD! %i\n", angle);
			alive = 0;
			return;
		}
		
		f->r = s->r / 2;
		f->velocity = FANT_JUMP_VELOCITY;
	}


	/* Handle rotation */

	f->angle += f->d_angle * d_last_frame_time() / 1000;
	angle *= -1;
	sin = d_util_sin(angle);
	cos = d_util_sin(angle + 900);
	x = 0;
	y = - f->r;
	//y = - d_sprite_height(f->sprite) / 2;
	x_o = cos * x - sin * y;
	y_o = sin * x + cos * y;
	x_o /= 65536;
	y_o /= 65536;

	x_o += s->r / 2 - d_sprite_width(f->sprite) / 2;
	y_o += s->r / 2 - d_sprite_height(f->sprite);

	d_sprite_rotate(f->sprite, (angle - 900) * -1);
	d_sprite_move(f->sprite, x_o, y_o);

	return;
}

void fant_draw(struct fant *f) {
	d_render_blend_enable();
	d_sprite_draw(f->sprite);
	d_render_blend_disable();

	return;
}


