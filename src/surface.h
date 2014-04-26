#ifndef __SURFACE_H__
#define	__SURFACE_H__

#define	SURFACE_DMG_COUNT_START	4
#define	SURFACE_THICKNESS	32
#define	SURFACE_DMG_ARTEFACT	128

struct surface_segment {
	int			damage;
	int			type;
};


struct surface {
	int			angle;
	unsigned int		*pixbuff;
	int			pixbuf_w;
	int			pixbuf_h;
	int			r;

	struct surface_segment	*seg;
	int			segs;
};

struct surface *surface_init(int r, int segs);
void surface_segment_update_graphics(struct surface *s, int seg);
void surface_generate(struct surface *s);


#endif
