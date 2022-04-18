#include "draw.h"
#include "vect2.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

void draw(obj* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < PAST_POSITIONS_NUM - 1; j++)
        {
            al_draw_line(arr[i].past_positions[j].x, arr[i].past_positions[j].y, arr[i].past_positions[j + 1].x, arr[i].past_positions[j + 1].y,
            al_map_rgb(255,255,255), 1.0);
        }
        al_draw_circle(arr[i].position.x, arr[i].position.y, arr[i].radius, al_map_rgb(255,0,0), 1.0);
        draw_v(arr[i].position, arr[i].velocity, 5.0, al_map_rgb(255, 255, 0));
        draw_v(arr[i].position, arr[i].acceleration, 100.0, al_map_rgb(0,255,0));
    }
}
