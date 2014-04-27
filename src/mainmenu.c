#include "fanten.h"
#include "mainmenu.h"
#include "state.h"
#include <darnit/darnit.h>

DARNIT_MENU *main_menu;


void mainmenu_init() {
	main_menu = d_menu_vertical_new("  NEW GAME\nHOW TO PLAY\n HIGHSCORE\n  CREDITS \n QUIT GAME", 305, 250, font, 200, 20, 500);

	return;
}


void mainmenu_prepare() {
	d_menu_selection_wait(main_menu);

	return;
}


void mainmenu_draw() {
	int selection;
	
	d_render_blend_enable();
	selection = d_menu_loop(main_menu);
	d_render_blend_disable();

	switch (selection) {
		case -1:
			break;
		case 0:
			state.next_state = STATE_GAMEPLAY;
			break;
		case 2:
			state.next_state = STATE_HIGHSCORE;
			break;
		default:
		case -2:
		case 4:
			fprintf(stderr, "Selection %i, quitting\n", selection);
			d_quit();
			break;
	}

	return;
}
