#ifndef __FANTEN_H__
#define	__FANTEN_H__


#include <darnit/darnit.h>
#include "highscore.h"

extern DARNIT_FONT *font;
int score;
int alive;
struct highscore *h;

void fanten_gamestate_new();
void fanten_gamestate_destroy();


#endif
