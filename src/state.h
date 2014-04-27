#ifndef __STATE_H__
#define	__STATE_H__

#define	STATE_FADE_TIME		1000

enum state_num {
	STATE_DUMMY,
	STATE_MAINMENU,
	STATE_GAMEPLAY,
	STATE_NEWHIGHSCORE,
	STATE_HIGHSCORE,
	STATE_CREDITS,
};


struct {
	enum state_num cur_state;
	enum state_num next_state;
} state;


void state_init();
void state_loop();

#endif
