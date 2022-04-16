#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>

int main()
{
    if (!al_init())
		return 1;

	if (!al_install_keyboard())
		return 1;

	if (!al_init_primitives_addon())
		return 1;

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

    ALLEGRO_DISPLAY* display = al_create_display(1920, 1080);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    float n = 0.0;
    ALLEGRO_EVENT event;
    while (true)
	{
		al_wait_for_event(event_queue, &event);
		if (event.keyboard.keycode == ALLEGRO_KEY_K)
			break;
		al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_circle(n, n, 500.0, al_map_rgb(255,255,255), 100.0);
		al_flip_display();
        clock_t start_time = clock();
        while (clock() < start_time + 200);
        n += 1;
	}
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}

