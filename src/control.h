#ifndef CONTROL_H
#define CONTROL_H

#include <allegro5/events.h>
#include <allegro5/transformations.h>

typedef struct loop_ctrl
{
	int alive;
	int pause;
	int step;
} loop_ctrl;

typedef struct cam_ctrl
{
	float tx;
	float ty;
	float sx;
	float sy;
	float rot_angle;
} cam_ctrl;

void manage_event(ALLEGRO_EVENT_QUEUE* eq, ALLEGRO_EVENT* e, loop_ctrl* l_ctrl);
void transform(ALLEGRO_TRANSFORM* t, const cam_ctrl* c_ctrl);

#endif
