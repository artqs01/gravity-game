#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main()
{
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
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    float n = 0.0;
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Main loop
    int alive = 1;
    while (alive)
	{
        // Checking events from player
		al_wait_for_event(event_queue, &event);
        do
        {
            if (event.type == ALLEGRO_EVENT_KEY_DOWN)
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			        alive = 0;
        } while (al_get_next_event(event_queue, &event));

        // Drawing
		al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_filled_circle(n, n, 30.0, al_map_rgb(255,255,255));
		al_flip_display();
        n += 1;
	}

    // Cleaning up
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    return 0;
}
