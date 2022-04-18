#ifndef OBJ_H
#define OBJ_H

#include "vect2.h"

#define G_CONST 1000
#define COR 0.7f
#define PAST_POSITIONS_NUM 128

typedef struct obj
{
    float radius;
    float mass;
    vect2 position;
    vect2 velocity;
    vect2 past_positions[PAST_POSITIONS_NUM];
} obj;

void obj_update(obj* arr, int size, float dt);
void obj_interact(obj* o1, obj* o2, float dt);
void obj_move(obj* o, float dt);
void obj_collide(obj* o1, obj* o2);
float obj_force(obj o1, obj o2);
float obj_collision_prediction(obj* o1, obj* o2, float dt);
vect2 obj_force_vect(obj o, obj interactor);

#endif
