#include <darnit/darnit.h>
#include "surface.h"
#include "trampoline.h"
#include "fant.h"

#define	CIRCLE_SIZE		1024


int main(int argc, char **argv) {
	struct surface *s;
	struct trampoline *t;
	struct fant *f;
	int i;

	d_init("Fanten: Breaking Beneath the Surface", "fanten-bbts", NULL);

	s = surface_init(CIRCLE_SIZE, 16);
	surface_generate(s);
	t = trampoline_init(s);
	f = fant_init(s);

	for (i = 0;; i++) {
		d_render_offset(s->r / 2 - 400, -340);
		d_render_begin();
		fant_move(s, f, i * 10);
		surface_draw(s);
		trampoline_draw(t);
		fant_draw(f);
		d_render_end();
		d_loop();
	}

	return 0;
}
