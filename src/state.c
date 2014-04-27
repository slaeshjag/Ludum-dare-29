#include "state.h"
#include "fanten.h"
#include "surface.h"
#include "trampoline.h"
#include "fant.h"
#include "control.h"
#include "highscore.h"
#include "mainmenu.h"

extern struct surface *s;
extern struct trampoline *t;
extern struct fant *f;
extern struct control *c;

void state_init() {
	state.cur_state = STATE_DUMMY;
	state.next_state = STATE_MAINMENU;

	return;
}


void state_loop() {
	if (state.cur_state != state.next_state) {
		d_render_fade_in(STATE_FADE_TIME, 0, 0, 0);
		if (d_render_fade_status() == 2) {
			/* Clean up old state */
			switch (state.cur_state) {
				case STATE_DUMMY:
				case STATE_MAINMENU:
					fanten_gamestate_destroy();
					break;
				case STATE_GAMEPLAY:
					fanten_gamestate_destroy();
					break;
				case STATE_NEWHIGHSCORE:
				case STATE_HIGHSCORE:
					fanten_gamestate_destroy();
					break;
				case STATE_CREDITS:
					break;
			}

			/* Create new state */
			switch (state.next_state) {
				case STATE_DUMMY:
				case STATE_MAINMENU:
					mainmenu_prepare();
					fanten_gamestate_new();
					break;
				case STATE_GAMEPLAY:
					fanten_gamestate_new();
					break;
				case STATE_NEWHIGHSCORE:
				case STATE_HIGHSCORE:
					fanten_gamestate_new();
					highscore_prepare(h);
					break;
				case STATE_CREDITS:
					break;
			}
			
			state.cur_state = state.next_state;
			d_render_fade_out(STATE_FADE_TIME);
		}
		/* TODO: Check fading */
	}

	switch (state.cur_state) {
		case STATE_DUMMY:
			break;
		case STATE_MAINMENU:
			d_render_offset(s->r / 2 - 400, -200);
			surface_draw(s);
			trampoline_draw(t);
			fant_draw(f);
			d_render_offset(0, 0);
			mainmenu_draw();
			break;
		case STATE_GAMEPLAY:
			if (alive)
				control_loop(s, t, f, c);
			else {
				d_render_offset(s->r / 2 - 400, -400);
				surface_draw(s);
				trampoline_draw(t);
				fant_draw(f);
				state.next_state = STATE_NEWHIGHSCORE;
				d_render_offset(0, 0);
			}
			break;
		case STATE_NEWHIGHSCORE:
			if (!highscore_new(h, score))
				state.next_state = STATE_HIGHSCORE;
			break;
		case STATE_HIGHSCORE:
			highscore_draw(h);
			break;
		case STATE_CREDITS:
			break;
	}

	return;
}
