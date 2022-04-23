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
            al_draw_line(arr[i].past_p[j].x, arr[i].past_p[j].y, arr[i].past_p[j + 1].x, arr[i].past_p[j + 1].y,
            al_map_rgb(255,255,255), 1.0);
        }
        // al_draw_filled_circle(arr[i].p.x, arr[i].p.y, arr[i].r, al_map_rgb(100,0,0));
        al_draw_circle(arr[i].p.x, arr[i].p.y, arr[i].r, (arr[i].q >= 0) ? al_map_rgb(255,0,0) : al_map_rgb(0,0,255), 2.0f);
    }
}
