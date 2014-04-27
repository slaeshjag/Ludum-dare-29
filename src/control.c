#include "control.h"
#include "fant.h"
#include "surface.h"
#include "trampoline.h"
#include "fanten.h"

#include <darnit/darnit.h>
#include <string.h>

#define	ABS(x)		((x) < 0 ? (-x) : (x))

struct control *control_init() {
	struct control *c;

	c = malloc(sizeof(*c));
	c->angle = 0;
	c->a_vel = d_text_surface_new(font, 128, 800, 0, 0);

	return c;
}


void control_loop(struct surface *s, struct trampoline *t, struct fant *f, struct control *c) {
	char buff[256];
	int location, f_angle;

	/* Handle trampoline movement */
	if (d_keys_get().left)
		c->angle += d_last_frame_time() / 4;
	if (d_keys_get().right)
		c->angle -= d_last_frame_time() / 4;

	surface_rotate(s, -c->angle);
	fant_move(s, f, c->angle);

	/* Update stats */
	f_angle = f->angle + s->angle;
	f_angle %= 3600;
	if (f_angle < 0) f_angle = 3600 + f_angle;
	d_text_surface_reset(c->a_vel);
	sprintf(buff, "Angular velocity: %.2f deg/s\n", (float) f->d_angle / 10);
	d_text_surface_string_append(c->a_vel, buff);
	sprintf(buff, "Surface location: %.2f deg\n", (float) (f_angle) / 10);
	d_text_surface_string_append(c->a_vel, buff);
	sprintf(buff, "Score: %.5i", score);
	d_text_surface_string_append(c->a_vel, buff);

	/* Render */
	d_render_offset(s->r / 2 - 400, -400);
	surface_draw(s);
	trampoline_draw(t);
	fant_draw(f);

	d_render_blend_enable();
	d_render_offset(0, 0);
	d_text_surface_draw(c->a_vel);
	d_render_blend_disable();

	return;
}
