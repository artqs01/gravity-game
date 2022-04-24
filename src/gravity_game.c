#include "obj.h"
#include "draw.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
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
    // Event queue init
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_EVENT event;
	al_register_event_source(event_queue, al_get_keyboard_event_source());
    // Timer init
    ALLEGRO_TIMER* timer =  al_create_timer(0.013);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    // Display init
    ALLEGRO_DISPLAY* display = al_create_display(1200, 900);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    //Font init
    ALLEGRO_FONT* font = al_load_ttf_font("/home/artqs01/Dane/MojeZabawyCCpp/gravity_game/fonts/consola.ttf", 20, 0);
    if (!font)
    {
        printf("\n\nnie zaladowalo fonta\n\n");
        return 1;
    }
    al_register_event_source(event_queue, al_get_keyboard_event_source());
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
    int alive = 1;
    int pause = 0;
    int step = 0;
    double t1 = al_get_time();
    double t2;
    float dt;
    while (alive)
	{
        t2 = al_get_time();
        dt = t2 - t1;
        t1 = t2;
		al_wait_for_event(event_queue, &event);
        do
        {
            if (event.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			        alive = 0;
                if (event.keyboard.keycode == ALLEGRO_KEY_P)
                {
                    pause = !pause;
                }
                if (event.keyboard.keycode == ALLEGRO_KEY_S)
                {
                    pause = 0;
                    step = 1;
                }
            }
        } while (al_get_next_event(event_queue, &event));
        if (!pause)
        {
            if (step)
            {
                pause = 1;
                step = 0;
            }
            al_clear_to_color(al_map_rgb(0, 0, 0));
            obj_update(arro, size, dt);
            draw(arro, size, font);
            al_flip_display();
        }
	}
    // Cleaning up
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font);
    return 0;
}
