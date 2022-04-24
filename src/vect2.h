#ifndef VECT2_H
#define VECT2_H

#include <allegro5/color.h>
typedef struct vect2
{
	float x;
	float y;
} vect2;

vect2 vect2_add(vect2 v1, vect2 v2);
vect2 vect2_rot(vect2 v1, float angle);
vect2 vect2_rtc(vect2 v1, vect2 center, float angle);
vect2 vect2_mlf(vect2 v, float f);
vect2 vect2_neg(vect2 v);
vect2 vect2_sub(vect2 v, vect2 subtractor);
vect2 vect2_nrm(vect2 v);
float vect2_dot(vect2 v1, vect2 v2);
float vect2_det(vect2 v1, vect2 v2);
float vect2_len(vect2 v);
float vect2_dst(vect2 v1, vect2 v2);
void draw_v(vect2 position, vect2 value, float scale, ALLEGRO_COLOR color);
float clampf(float x, float min_x, float max_x);

#endif
