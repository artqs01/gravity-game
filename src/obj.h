#ifndef OBJ_H
#define OBJ_H

#include "vect2.h"

#define G_CONST 1

typedef struct obj
{
    float radius;
    float density;
    vect2 position;
    vect2 velocity;
    vect2 past_positions[128];
} obj;

void obj_update(obj* arr, int size, float dt);
void obj_interact(obj* o1, obj* o2, float dt);
void obj_move(obj* o, float dt);
void obj_collision_check(obj* arr, int size);
void obj_collide(obj* o1, obj* o2);
float obj_mass(obj o);
float obj_force(obj o1, obj o2);
vect2 obj_force_vect(obj o, obj interactor);

#endif
