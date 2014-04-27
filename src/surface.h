#ifndef __SURFACE_H__
#define	__SURFACE_H__

#include <darnit/darnit.h>

#define	SURFACE_DMG_COUNT_START	4
#define	SURFACE_THICKNESS	32
#define	SURFACE_ROTATION_SPEED	80
#define	SURFACE_CRACK_WIDTH	20	/* in tenths on a degree */
#define	SURFACE_CRACK_AMPLITUDE	12
#define	SURFACE_DMG_ARTEFACT	128

struct surface_segment {
	int			damage;
	int			type;
};


struct surface {
	unsigned int		*pixbuff;
	int			pixbuf_w;
	int			pixbuf_h;
	int			r;

	struct surface_segment	*seg;
	int			segs;
	int			angle;
	int			cam_angle;

	DARNIT_TILESHEET	*srf;
	DARNIT_SPRITE		*sprite;
};

struct surface *surface_init(int r, int segs);
void *surface_destroy(struct surface *s);
void surface_segment_update_graphics(struct surface *s, int seg);
void surface_generate(struct surface *s);

void surface_draw(struct surface *s);
void surface_rotate(struct surface *s, int angle);

void surface_impact(struct surface *s, int angle);

#endif
