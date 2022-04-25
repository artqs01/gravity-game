#include "control.h"
#include <allegro5/keycodes.h>
#include <math.h>

ctrl_loop_ctrler ctrl_create_loop_ctrler()
{
	return (ctrl_loop_ctrler){1, 0, 0};
}

ctrl_cam_ctrler ctrl_create_cam_ctrler()
{
	return (ctrl_cam_ctrler){0.f, 600.f, 1.f, -1.f, 0.f, 0};
}

ctrl_time_ctrler ctrl_create_time_ctrler()
{
	return (ctrl_time_ctrler){0.0, al_get_time(), 0.f};
}

void ctrl_manage_event(ALLEGRO_EVENT_QUEUE* eq, ALLEGRO_EVENT *e, ctrl_loop_ctrler *l_ctrl)
{
	do
	{
		switch (e->type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE :
				l_ctrl->alive = 0;
			break;
			case ALLEGRO_EVENT_KEY_DOWN :
				if (e->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					l_ctrl->alive = 0;
				if (e->keyboard.keycode == ALLEGRO_KEY_P)
					l_ctrl->pause = !l_ctrl->pause;
				if (e->keyboard.keycode == ALLEGRO_KEY_S)
				{
					l_ctrl->pause = 0;
					l_ctrl->step = 1;
				}
			break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN :			
			break;
		}
	} while (al_get_next_event(eq, e));
}

void ctrl_transform(ALLEGRO_TRANSFORM* t, const ctrl_cam_ctrler* c_ctrl)
{
	al_build_transform(t,
		c_ctrl->tx,
		c_ctrl->ty,
		c_ctrl->sx,
		c_ctrl->sy,
		c_ctrl->rot_angle);
	al_use_transform(t);
}

void ctrl_mouse_state_update(ALLEGRO_MOUSE_STATE* cur_ms, ALLEGRO_MOUSE_STATE* prev_ms, ctrl_cam_ctrler* c_ctrl)
{
	if (c_ctrl->if_state_changed)
	{
		prev_ms = cur_ms;
		c_ctrl->if_state_changed = 0;
	}
	al_get_mouse_state(cur_ms);
}

void ctrl_set_zoom(ALLEGRO_MOUSE_STATE* cur_ms, ALLEGRO_MOUSE_STATE* prev_ms, ctrl_cam_ctrler* c_ctrl)
{
	if (prev_ms->z != cur_ms->z)
	{
		c_ctrl->sx = pow(1.1, cur_ms->z);
		c_ctrl->sy = -pow(1.1, cur_ms->z);
		c_ctrl->if_state_changed = 1;
	}
}

void ctrl_measure_dt(ctrl_time_ctrler* t_ctrl)
{
	t_ctrl->t_current = al_get_time();
	t_ctrl->dt = t_ctrl->t_current - t_ctrl->t_previous;
	t_ctrl->t_previous = t_ctrl->t_current;
}
