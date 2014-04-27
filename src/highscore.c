#include <darnit/darnit.h>
#include "highscore.h"
#include "fanten.h"
#include "surface.h"
#include <string.h>

extern struct surface *s;

void highscore_load(struct highscore *h) {
	DARNIT_FILE *f;

	f = d_file_open("highscore.dat", "rb");
	d_file_read(h->entry, sizeof(*h->entry) * HIGHSCORE_ENTRIES, f);
	d_file_close(f);

	return;
}


struct highscore *highscore_init() {
	struct highscore *h;

	h = malloc(sizeof(*h));
	memset(h, 0, sizeof(*h));

	h->highscore_table = d_text_surface_new(font, 1024, 800, 90, 150);

	return h;
}


void highscore_add(struct highscore *h, const char *name, int score) {
	int i;

	for (i = 0; i < HIGHSCORE_ENTRIES; i++)
		if (h->entry[i].score < score && score) {
			if (i + 1 < HIGHSCORE_ENTRIES)
				memmove(&h->entry[i + 1], &h->entry[i], sizeof(*h->entry) * (HIGHSCORE_ENTRIES - i - 1));
			strcpy(h->entry[i].name, name);
			h->entry[i].score = score;
			highscore_save(h);
			return;
		}
	return;
}


void highscore_save(struct highscore *h) {
	DARNIT_FILE *f;

	f = d_file_open("highscore.dat", "wb");
	d_file_write(h->entry, sizeof(*h->entry) * HIGHSCORE_ENTRIES, f);
	d_file_close(f);

	return;
}


int highscore_new(struct highscore *h, int score) {
	int i;

	for (i = 0; i < HIGHSCORE_ENTRIES; i++)
		if (h->entry[i].score < score)
			return 1;
	return 0;
}


void highscore_prepare(struct highscore *h) {
	char buff[1024];
	d_text_surface_reset(h->highscore_table);
	sprintf(buff, "................ HIGHSCORE ................\n\n\n\n");

	d_text_surface_string_append(h->highscore_table, buff);

	return;
}


void highscore_draw(struct highscore *h) {
	d_render_offset(s->r / 2 - 400, -200);
	surface_draw(s);
	d_render_offset(0, 0);
	d_render_blend_enable();
	d_text_surface_draw(h->highscore_table);
	d_render_blend_disable();

	return;
}
