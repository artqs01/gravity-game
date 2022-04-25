#ifndef INIT_H
#define INIT_H

#include <allegro5/events.h>
#include <allegro5/display.h>

void allegro_init();
void allegro_register_events(ALLEGRO_EVENT_QUEUE* eq, ALLEGRO_DISPLAY* d, struct ALLEGRO_TIMER* t);

#endif
