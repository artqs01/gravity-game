#include "init.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/display.h>
#include <allegro5/mouse.h>
#include <allegro5/transformations.h>
#include <allegro5/altime.h>
#include <allegro5/color.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

void allegro_init()
{
	int err = 0;
	if (!al_init())
		err = -1;
	if (!al_install_keyboard())
	{
		printf("syf al_install_keyboard");
		err = -2;
	}
	if (!al_install_mouse())
	{
		printf("syf al_install_mouse");
		err = -3;
	}
	if (!al_init_primitives_addon())
	{
		printf("syf al_primitives");
		err = -4;
	}
	if (!al_init_font_addon())
	{
		printf("syf al_font");
		err = -5;
	}
	if (!al_init_ttf_addon())
	{
		printf("syf al_font_ttf");
		err = -6;
	}
	switch (err)
	{
		case -1 :
			printf("function \"al_init()\" not working!\n");
		break;
		case -2 :
			printf("function \"al_install_keyboard()\" not working!\n");
		break;
		case -3 :
			printf("function \"al_install_mouse()\" not working!\n");
		break;
		case -4 :
			printf("function \"al_init_primitives_addon()\" not working!\n");
		break;
		case -5 :
			printf("function \"al_init_font_addon()\" not working!\n");
		break;
		case -6 :
			printf("function \"al_init_ttf_addon()\" not working!\n");
		break;
	}
}

void allegro_register_events(ALLEGRO_EVENT_QUEUE* eq, ALLEGRO_DISPLAY* d, struct ALLEGRO_TIMER* t)
{
	al_register_event_source(eq, al_get_keyboard_event_source());
	al_register_event_source(eq, al_get_timer_event_source(t));
	al_register_event_source(eq, al_get_keyboard_event_source());
	al_register_event_source(eq, al_get_mouse_event_source());
	al_register_event_source(eq, al_get_display_event_source(d));
}
