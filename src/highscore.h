#ifndef __HIGHSCORE_H__
#define	__HIGHSCORE_H__

#define	HIGHSCORE_ENTRIES	5


#include <darnit/darnit.h>

struct highscore_entry {
	int			score;
	char			name[32];
};


struct highscore {
	struct highscore_entry	entry[HIGHSCORE_ENTRIES];
	DARNIT_TEXT_SURFACE	*highscore_table;
};


void highscore_load(struct highscore *h);
struct highscore *highscore_init();
void highscore_add(struct highscore *h, const char *name, int score);
void highscore_save(struct highscore *h);
int highscore_new(struct highscore *h, int score);
void highscore_prepare(struct highscore *h);


#endif
