#ifndef DRAW_H
#define DRAW_H

#include "obj.h"
#include <allegro5/allegro_font.h>
#include <allegro5/color.h>

#define DISP_0_EPSILON_UP 10.f
#define DISP_0_EPSILON_DOWN -DISP_0_EPSILON_UP

void draw(obj* arr, int size, const ALLEGRO_FONT* font);
ALLEGRO_COLOR map_q_on_color(float q, float down_q, float up_q);

#endif
