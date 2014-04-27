#include <darnit/darnit.h>
#include "surface.h"
#include "trampoline.h"
#include "fant.h"
#include "control.h"
#include "fanten.h"
#include "state.h"

#define	CIRCLE_SIZE		1024

DARNIT_FONT *font;

struct surface *s;
struct trampoline *t;
struct fant *f;
struct control *c;

void fanten_gamestate_new() {
	s = surface_init(CIRCLE_SIZE, 16);
	surface_generate(s);
	t = trampoline_init(s);
	f = fant_init(s);
	c = control_init();
	fant_move(s, f, 0);

	score = 0;
	alive = 1;
	return;
}


void fanten_gamestate_destroy() {
	s = surface_destroy(s);
	t = trampoline_destroy(t);
	f = fant_destroy(f);
	c = control_destroy(c);
}


int main(int argc, char **argv) {
	int i;

	d_init_custom("Fanten: Breaking Beneath the Surface", 800, 600, 0, "fanten-bbts", NULL);

	font = d_font_load("res/font.ttf", 24, 64, 64);
	d_fs_mount_self();
	h = highscore_init();
	state_init();
	mainmenu_init();

	for (i = 0;; i++) {
		d_render_begin();
		state_loop();
		d_render_end();
		d_loop();
	}

	return 0;
}
