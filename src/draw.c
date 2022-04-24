#include "draw.h"
#include "vect2.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/color.h>
#include <stdio.h>

void draw(obj* arr, int size, const ALLEGRO_FONT* font)
{
    for (int i = 0; i < size; i++)
    {
        // al_draw_filled_circle(arr[i].p.x, arr[i].p.y, arr[i].r, map_q_on_color(arr[i].q, MIN_Q, MAX_Q));
        al_draw_circle(arr[i].p.x, arr[i].p.y, arr[i].r, map_q_on_color(arr[i].q, MIN_Q, MAX_Q), 1.7f);
        char q_c;
        if (arr[i].q < DISP_0_EPSILON_DOWN)
            q_c = '-';
        else if (arr[i].q > DISP_0_EPSILON_UP)
            q_c = '+';
        else
            q_c = '0';
        al_draw_textf(font, al_map_rgb(255, 255, 255), arr[i].p.x - 5, arr[i].p.y - 8, 0, "%c", q_c);
    }
}

ALLEGRO_COLOR map_q_on_color(float q, float down_q, float up_q)
{
    int color_value = ((float)(q - down_q) / (float)(up_q - down_q) * 511);
    return (color_value < 256) ?
        al_map_rgb(color_value, color_value, 255) :
        al_map_rgb(255, 511 - color_value, 511 - color_value);
}
