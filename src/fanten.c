#include <darnit/darnit.h>
#include "surface.h"
#include "trampoline.h"
#include "fant.h"
#include "control.h"

#define	CIRCLE_SIZE		1024

DARNIT_FONT *font;

int main(int argc, char **argv) {
	struct surface *s;
	struct trampoline *t;
	struct fant *f;
	struct control *c;
	int i;

	d_init("Fanten: Breaking Beneath the Surface", "fanten-bbts", NULL);

	font = d_font_load("res/font.ttf", 24, 64, 64);
	s = surface_init(CIRCLE_SIZE, 16);
	surface_generate(s);
	t = trampoline_init(s);
	f = fant_init(s);
	c = control_init();
	fant_move(s, f, 0);

	for (i = 0;; i++) {
		d_render_begin();
		control_loop(s, t, f, c);
		d_render_end();
		d_loop();
	}

	return 0;
}
