#include "surface.h"
#include "fanten.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define	DEG_TO_RAD(x)		((float) (x) * M_PI / 1800.f)


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

	s->srf = d_render_tilesheet_new(1, 1, r, r, DARNIT_PFORMAT_RGB5A1);
	s->sprite = d_sprite_new(s->srf);
	s->angle = 0;
	s->cam_angle = 0;
	d_sprite_frame_entry_set(s->sprite, 0, 0, 0, 200);
	d_sprite_move(s->sprite, 0, 0);
	d_sprite_activate(s->sprite, 0);

	return s;
}


void *surface_destroy(struct surface *s) {
	if (!s)
		return NULL;
	free(s->pixbuff);
	free(s->seg);
	d_render_tilesheet_free(s->srf);
	d_sprite_free(s->sprite);
	free(s);

	return NULL;
}


void surface_segment_spawn_crack(struct surface *s, int seg) {
	int seg_width, center, wiggle, pos, h_wiggle, h_pos, x, y, i, p, old_h, j, dj, d;

	seg_width = 3600 / s->segs;
	center = seg_width * seg + seg_width/2;
	wiggle = seg_width - SURFACE_CRACK_WIDTH / 2;
	pos = rand() % wiggle + center - seg_width / 2;
	pos -= SURFACE_CRACK_WIDTH / 2;
	h_wiggle = SURFACE_THICKNESS - SURFACE_CRACK_AMPLITUDE;
	h_pos = rand() % h_wiggle + s->r / 2 - SURFACE_THICKNESS + SURFACE_CRACK_AMPLITUDE / 2;
	old_h = 42;

	for (i = 0; i < SURFACE_CRACK_WIDTH; i += 2) {
		p = h_pos + (rand() % SURFACE_CRACK_AMPLITUDE - SURFACE_CRACK_AMPLITUDE / 2);
		j = p;
		if (old_h != 42) {
			dj = (old_h > p) ? 1 : -1;
			if (old_h == p)
				old_h += dj;
		} else {
			old_h = p + 1;
			dj = 1;
		}

		for (d = 0; j != old_h; j += dj, d += dj) {
			x = cosf(DEG_TO_RAD(pos + i)) * (p + d) + s->r / 2;
			y = sinf(DEG_TO_RAD(pos + i)) * (p + d) + s->r / 2;
			
			s->pixbuff[x + y * s->pixbuf_w] = 0xFF000022;
		}

		old_h = p;
	}
	/* TODO: Optimize */
	d_render_tilesheet_update(s->srf, 0, 0, s->pixbuf_w, s->pixbuf_h, s->pixbuff);
}


void surface_floodfill_interior(struct surface *s, int x, int y, int max_x) {
	int g;

	if (x < 0 || x >= max_x)
		return;
	if (y < 0 || y >= s->pixbuf_h)
		return;
	if (s->pixbuff[x + y * s->pixbuf_w])
		/* Not black */
		return;
	g = ((x - s->r / 2) * (x - s->r / 2) + (y - s->r / 2) * (y - s->r / 2)) * 255 / ((s->r / 2) * (s->r / 2));
	g &= 0xFF;
	g = 255 - g;
	g <<= 8;
	s->pixbuff[x + y * s->pixbuf_w] = (0xFF0000FF | g);
	//s->pixbuff[x + y * s->pixbuf_w] = (0xFF000080 | ((255 * (x * x + y * y) / s->r * s->r) << 8));

	surface_floodfill_interior(s, x + 1, y, max_x);
	surface_floodfill_interior(s, x - 1, y, max_x);
	surface_floodfill_interior(s, x, y + 1, max_x);
	surface_floodfill_interior(s, x, y - 1, max_x);

	return;
}


void surface_segment_update_graphics(struct surface *s, int seg) {
	int steps, d_deg, x, y, i, j, r_base, x_min, x_max, y_min, y_max;
	float deg_start, d_step;

	x_min = y_min = INT_MIN;
	y_max = x_max = INT_MAX;

	d_deg = 3600 / s->segs;
	deg_start = d_deg * seg;
	
	/* Should be enough steps */
	steps = s->pixbuf_w * 16 / s->segs;
	
	d_step = (float) d_deg / steps;
	r_base = s->r / 2 - SURFACE_THICKNESS - 1;

	for (i = 0; i < steps; i++) {
		for (j = 0; j < SURFACE_THICKNESS; j++) {
			x = cosf(DEG_TO_RAD(deg_start + d_step * i)) * (r_base + j) + (s->r / 2);
			y = sinf(DEG_TO_RAD(deg_start + d_step * i)) * (r_base + j) + (s->r / 2);
			if (x < x_min) x_min = x;
			if (y < y_min) y_min = y;
			if (x > x_max) x_max = x;
			if (y > y_max) y_max = y;
		
			/* 0xAABBGGRR */
//			if (steps/40 >= i)
//				s->pixbuff[x + y * s->pixbuf_w] = 0xFF000000;
			if (SURFACE_THICKNESS / 8 * 7 < j)
				s->pixbuff[x + y * s->pixbuf_w] = 0xFF00FF00;
			else if (SURFACE_THICKNESS / 8 * 5 > j)
				s->pixbuff[x + y * s->pixbuf_w] = 0xFF777777;
			else
				s->pixbuff[x + y * s->pixbuf_w] = 0xFF004E7E;
		}
	}
	
	if (s->seg[seg].damage)
		surface_segment_spawn_crack(s, seg);
	

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

	for (i = 0; i < s->r / 32; i++) {
		surface_floodfill_interior(s, (i + 1) * 32 - s->r / 64, s->r / 2, (i + 1) * 32);
	}
	
	/* TODO: Optimize */
	d_render_tilesheet_update(s->srf, 0, 0, s->pixbuf_w, s->pixbuf_h, s->pixbuff);

	return;
}


void surface_draw(struct surface *s) {
	s->angle += d_last_frame_time() * SURFACE_ROTATION_SPEED / 1000;
	d_render_blend_enable();
	d_sprite_rotate(s->sprite, s->angle + s->cam_angle); 
	d_sprite_draw(s->sprite);
	d_render_blend_disable();

	return;
}


void surface_rotate(struct surface *s, int angle) {
	s->cam_angle = angle;
	
	return;
}


void surface_impact(struct surface *s, int angle) {
	if (angle < 0)
		angle = 3600  +angle;
	angle += 2700;

	angle %= 3600;
	angle /= (3600 / s->segs);
	if (s->seg[angle].damage)
		s->seg[angle].damage++, surface_segment_spawn_crack(s, angle), score += (s->segs / SURFACE_DMG_COUNT_START);
	else
		score -= 2;
	if (score < 0)
		score = 0;
	return;
}
