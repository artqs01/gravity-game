#include "draw.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

void draw(obj* arr, int size)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < PAST_POSITIONS_NUM - 1; j++)
        {
            al_draw_line(arr[i].past_positions[j].x, arr[i].past_positions[j].y, arr[i].past_positions[j + 1].x, arr[i].past_positions[j + 1].y,
            al_map_rgb(255,255,255), 1.0);
        }
        al_draw_filled_circle(arr[i].position.x, arr[i].position.y, arr[i].radius, al_map_rgb(255,0,0));
    }
}
