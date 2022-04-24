#ifndef OBJ_H
#define OBJ_H

#include "vect2.h"

#define G_CONST 2.f
#define K_CONST 3.5f
#define COR 0.7f
#define PAST_POSITIONS_NUM 1
#define DAMPING_CONST 0.1f
#define MAX_Q 1000.f
#define MIN_Q -1000.f

typedef struct obj
{
    float r;
    float m;
    float q;
    vect2 p;
    vect2 v;
    vect2 dv;
} obj;

obj obj_create(float radius, float m, float q, vect2 p, vect2 v);
void obj_apply_impulse(obj* o, vect2 , float dt);
void obj_update_wrong(obj* arr, int size, float dt);
void obj_update(obj* arr, int size, float dt);
void obj_interact(obj* arr, int size, float dt);
void obj_move(obj* o, float dt);
void obj_collide(obj* o1, obj* o2);
float obj_gravity_force_value(const obj* o1, const obj* o2);
float obj_coulomb_force_value(const obj* o1, const obj* o2);
float obj_collision_prediction(obj* o1, obj* o2);
vect2 obj_force_vect(const obj* o, const obj* interactor, float(*value)(const obj*, const obj*));

#endif
