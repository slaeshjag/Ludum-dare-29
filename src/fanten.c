#include <darnit/darnit.h>
#include "surface.h"
#include "trampoline.h"

#define	CIRCLE_SIZE		512


int main(int argc, char **argv) {
	DARNIT_TILESHEET *surface;
	struct surface *s;
	struct trampoline *t;

	d_init("Fanten: Breaking Beneath the Surface", "fanten-bbts", NULL);

	surface = d_render_tilesheet_new(1, 1, CIRCLE_SIZE, CIRCLE_SIZE, DARNIT_PFORMAT_RGBA8);
	s = surface_init(CIRCLE_SIZE, 16);
	surface_generate(s);
	d_render_tilesheet_update(surface, 0, 0, CIRCLE_SIZE, CIRCLE_SIZE, s->pixbuff);
	t = trampoline_init(s);

	for (;;) {
		d_render_begin();
		d_render_tile_blit(surface, 0, 0, 32);
		trampoline_draw(t);
		d_render_end();
		d_loop();
	}

	return 0;
}
