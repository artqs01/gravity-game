#ifndef OBJ_H
#define OBJ_H

#include "vect2.h"

#define G_CONST 6
#define COR 0.7f
#define PAST_POSITIONS_NUM 128
#define DAMPING_CONST 1.f

typedef struct obj
{
    float r;
    float m;
    vect2 p;
    vect2 v;
    vect2 dv;
    vect2 past_p[PAST_POSITIONS_NUM];
} obj;

obj obj_create(float radius, float m, vect2 p, vect2 v);
void obj_apply_impulse(obj* o, vect2 , float dt);
void obj_update_wrong(obj* arr, int size, float dt);
void obj_update(obj* arr, int size, float dt);
void obj_interact(obj* arr, int size, float dt);
void obj_move(obj* o, float dt);
void obj_collide(obj* o1, obj* o2);
float obj_force(obj o1, obj o2);
float obj_collision_prediction(obj* o1, obj* o2);
vect2 obj_force_vect(obj o, obj interactor);

#endif
