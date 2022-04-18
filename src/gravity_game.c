#include "obj.h"
#include "draw.h"
#include "vect2.h"

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
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // obj arro[20];
    // for (int i = 0; i < 20; i++) 
    // {
    //     arro[i] = (obj)
    //     {
    //         rand_f(3.0, 10.0),
    //         rand_f(700, 2000),
    //         (vect2){rand_f(0.0,800.0), rand_f(0.0, 600.0)},
    //         (vect2){rand_f(-20.0, 20.0), rand_f(-20.0, 20.0)},
    //     };
    //     for (int j = 0; j < PAST_POSITIONS_NUM; j++)
    //     {
    //         arro[i].past_positions[j] = arro[i].position;
    //     }
    // }
    obj arro[] = 
    {
        {
            50.0,
            20000.0,
            (vect2){300.0, 300.0},
            (vect2){00.0, 0.0}
        },
        {
            10.0,
            2000.0,
            (vect2){500.0, 500.0},
            (vect2){-00.0, 0.0}
        },
    };
    const int size = sizeof(arro) / sizeof(obj);

    for (int i = 0; i < PAST_POSITIONS_NUM; i++)
    {
        arro[0].past_positions[i] = arro[0].position;
        arro[1].past_positions[i] = arro[1].position;
    }

    // Main loop 
    int alive = 1;
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
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			        alive = 0;
        } while (al_get_next_event(event_queue, &event));
		draw(arro, size);
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
            {
                if (vect2_dst(arro[i].position, arro[j].position) < arro[i].radius + arro[j].radius)
                    printf("Nakładają się! dst = %f, R = %f\n", vect2_dst(arro[i].position, arro[j].position), arro[i].radius + arro[j].radius);
            }
        obj_update(arro, size, dt);
		al_flip_display();
	}

    // Cleaning up
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    return 0;
}
