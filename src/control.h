#ifndef CONTROL_H
#define CONTROL_H

#include <allegro5/events.h>
#include <allegro5/mouse.h>
#include <allegro5/transformations.h>

typedef struct ctrl_loop_ctrler
{
	int alive;
	int pause;
	int step;
} ctrl_loop_ctrler;

typedef struct ctrl_cam_ctrler
{
	float tx;
	float ty;
	float sx;
	float sy;
	float rot_angle;
	int if_state_changed;
} ctrl_cam_ctrler;

typedef struct ctrl_time_ctrler
{
	double t_current;
	double t_previous;
	float dt;
} ctrl_time_ctrler;

ctrl_loop_ctrler ctrl_create_loop_ctrler();
ctrl_cam_ctrler ctrl_create_cam_ctrler();
ctrl_time_ctrler ctrl_create_time_ctrler();
void ctrl_manage_event(ALLEGRO_EVENT_QUEUE* eq, ALLEGRO_EVENT* e, ctrl_loop_ctrler* l_ctrl);
void ctrl_transform(ALLEGRO_TRANSFORM* t, const ctrl_cam_ctrler* c_ctrl);
void ctrl_mouse_state_update(ALLEGRO_MOUSE_STATE* cur_ms, ALLEGRO_MOUSE_STATE* prev_ms, ctrl_cam_ctrler* c_ctrl);
void ctrl_set_zoom(ALLEGRO_MOUSE_STATE* cur_ms, ALLEGRO_MOUSE_STATE* prev_ms, ctrl_cam_ctrler* c_ctrl);
void ctrl_measure_dt(ctrl_time_ctrler* t_ctrl);

#endif
