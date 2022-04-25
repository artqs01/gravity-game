#include "control.h"
#include <allegro5/keycodes.h>

void manage_event(ALLEGRO_EVENT_QUEUE* eq, ALLEGRO_EVENT *e, loop_ctrl *l_ctrl)
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

void transform(ALLEGRO_TRANSFORM* t, const cam_ctrl* c_ctrl)
{
	al_build_transform(t,
		c_ctrl->tx,
		c_ctrl->ty,
		c_ctrl->sx,
		c_ctrl->sy,
		c_ctrl->rot_angle);
	al_use_transform(t);
}

