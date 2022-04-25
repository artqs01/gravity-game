#include "obj.h"
#include "draw.h"
#include "control.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/display.h>
#include <allegro5/mouse.h>
#include <allegro5/transformations.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/altime.h>
#include <allegro5/color.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>

float rand_f(float down, float up)
{
	return (float)rand() / (float)RAND_MAX * (up - down) + down;
}

int main()
{
	srand(time(0));
	// Checking if things fail to init
	if (!al_init())
	{
		printf("syf al_init");
		return 1;
	}
	if (!al_install_keyboard())
	{
		printf("syf al_keyboard");
		return 1;
	}
	if (!al_install_mouse())
	{
		printf("syf al_keyboard");
		return 1;
	}
	if (!al_init_primitives_addon())
	{
		printf("syf al_primitives");
		return 1;
	}
	if (!al_init_font_addon())
	{
		printf("syf al_font");
		return 1;
	}
	if (!al_init_ttf_addon())
	{
		printf("syf al_font_ttf");
		return 1;
	}

	// Timer init
	ALLEGRO_TIMER* timer =  al_create_timer(0.013);
	al_start_timer(timer);

	// Display init
	ALLEGRO_DISPLAY* display = al_create_display(1200, 900);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	// Event queue init
	ALLEGRO_EVENT_QUEUE* eq = al_create_event_queue();
	ALLEGRO_EVENT e;
	al_register_event_source(eq, al_get_keyboard_event_source());
	al_register_event_source(eq, al_get_timer_event_source(timer));
	al_register_event_source(eq, al_get_keyboard_event_source());
	al_register_event_source(eq, al_get_mouse_event_source());
	al_register_event_source(eq, al_get_display_event_source(display));

	//Font init
	ALLEGRO_FONT* font = al_load_ttf_font("/home/artqs01/Dane/MojeZabawyCCpp/gravity_game/fonts/consola.ttf", 20, 0);
	if (!font)
	{
		printf("\n\nnie zaladowalo fonta\n\n");
		return 1;
	}

	//Mouse control init
	ALLEGRO_MOUSE_STATE cur_ms;
	al_get_mouse_state(&cur_ms);
	ALLEGRO_MOUSE_STATE prev_ms;

	//Camera transformation init
	ALLEGRO_TRANSFORM transf;
	ctrl_cam_ctrler c_ctrl = ctrl_create_cam_ctrler();

	// Main loop control variable init
	ctrl_loop_ctrler l_ctrl = ctrl_create_loop_ctrler();

	// Time measure variable init
	ctrl_time_ctrler t_ctrl = ctrl_create_time_ctrler();

	// Object initialization
	// obj arro[200];
	// for (int i = 0; i < 200; i++) 
	// {
	//     arro[i] = obj_create(
	//         rand_f(20.f, 30.f),
	//         rand_f(200.f, 300.f),
	//         rand_f(MIN_Q, MAX_Q),
	//         (vect2){rand_f(0.f,1000.f),rand_f(0.f, 1000.f)},
	//         (vect2){rand_f(-0.f, 0.f), rand_f(-0.f, 0.f)});
	// }
	obj arro[2];
	arro[0] = obj_create(20.f, 1000.f, -1000.f, (vect2){300.f, 300.f}, (vect2){10.f, 0.f});
	arro[1] = obj_create(10.f, 100.f, 1000.f, (vect2){600.f, 600.f}, (vect2){0.f, -10.f});
	const int size = sizeof(arro) / sizeof(obj);

	// Main loop
	while (l_ctrl.alive)
	{
		ctrl_measure_dt(&t_ctrl);
		al_wait_for_event(eq, &e);
		ctrl_manage_event(eq, &e, &l_ctrl);
		if (!l_ctrl.pause)
		{
			obj_update(arro, size, t_ctrl.dt);
		}
		if (l_ctrl.step)
		{
			l_ctrl.pause = 1;
			l_ctrl.step = 0;
		}
		ctrl_set_zoom(&cur_ms, &prev_ms, &c_ctrl);
		ctrl_transform(&transf, &c_ctrl);
		ctrl_mouse_state_update(&cur_ms, &prev_ms, &c_ctrl);
		draw(arro, size, font);
		al_flip_display();
	}
	
	// Cleaning up
	al_destroy_display(display);
	al_destroy_event_queue(eq);
	al_destroy_timer(timer);
	al_destroy_font(font);
	return 0;
}
