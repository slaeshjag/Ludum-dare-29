#include "surface.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	DEG_TO_RAD(x)		((x) * M_PI / 18000.f)


struct surface *surface_init(int r, int segs) {
	/* Segments have evenly divided angular distance */
	struct surface *s;

	s = malloc(sizeof(*s));
	s->angle = 0;
	s->pixbuff = malloc(sizeof(*s->pixbuff) * r * r);
	s->pixbuf_w = r;
	s->pixbuf_h = r;
	s->r = r;
	
	s->seg = malloc(sizeof(*s->seg) * segs);
	s->segs = segs;

	return s;
}


void surface_segment_update_graphics(struct surface *s, int seg) {
	int steps, d_deg, x, y, i, j, r_base;
	float deg_start, d_step;

	d_deg = 36000 / s->segs;
	deg_start = d_deg * seg;
	
	/* Should be enough steps */
	steps = 10 * s->pixbuf_w;
	
	d_step = (float) d_deg / steps;
	r_base = s->r / 2 - SURFACE_THICKNESS - 1;

	for (i = 0; i < steps; i++) {
		for (j = 0; j < SURFACE_THICKNESS; j++) {
			x = cosf(DEG_TO_RAD(deg_start + d_step * i)) * (r_base + j) + (s->r / 2);
			y = sinf(DEG_TO_RAD(deg_start + d_step * i)) * (r_base + j) + (s->r / 2);
		
			/* 0xAABBGGRR */
			if (!(rand() % (SURFACE_DMG_ARTEFACT - s->seg[seg].damage)) && s->seg[seg].damage) {
				/* TODO: Spawn "cracks" */
				/* Let's just get the base game up first... */
				s->pixbuff[x + y * s->pixbuf_w] = 0xFF0000FF;
			} else
				s->pixbuff[x + y * s->pixbuf_w] = 0xFF007777;
		}
	}

	return;
}


void surface_generate(struct surface *s) {
	int i, seg;

	memset(s->pixbuff, 0, sizeof(*s->pixbuff) * s->r * s->r);
	memset(s->seg, 0, sizeof(*s->seg) * s->segs);

	/* Generate segments */
	
	/* Pick four to be damaged from the start */
	for (i = 0; i < SURFACE_DMG_COUNT_START; i++) {
		seg = rand() % s->segs;
		if (s->seg[seg].damage) {
			i--;
			continue;
		}
		s->seg[seg].damage = 10;
	}

	/* TODO: Generate different types of segments to make the surface look more interesting */

	for (i = 0; i < s->segs; i++)
		surface_segment_update_graphics(s, i);

	return;
}
