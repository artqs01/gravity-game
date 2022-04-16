#ifndef OBJ_H
#define OBJ_H

#include "vect2.h"

typedef struct obj
{
    float r;
    float m;
    vect2 v;
    vect2 pos;
} obj;

void obj_collision_check(obj* arr, int size);
void obj_collide(obj o1, obj o2);
void obj_update_gravity(obj* arr, int size, float dt);

#endif
