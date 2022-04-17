#include "obj.h"
#include "vect2.h"

#include <math.h>
#include <stdio.h>

void obj_update(obj* arr, int size, float dt)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
        {
            obj_interact(&arr[i], &arr[j], dt);
            obj_move(&arr[i], dt);
            obj_move(&arr[j], dt);
            if (vect2_dst(arr[i].position, arr[j].position) <= arr[i].radius + arr[j].radius)
                obj_collide(&arr[i], &arr[j]);
        }
}

void obj_interact(obj* o1, obj* o2, float dt)
{
    vect2 dv_vect_for_o1 = vect2_mlf(vect2_mlf(obj_force_vect(*o1, *o2), 1 / obj_mass(*o1)), dt);
    o1->velocity = vect2_add(o1->velocity, dv_vect_for_o1);
    o2->velocity = vect2_add(o2->velocity, vect2_neg(dv_vect_for_o1));
}

void obj_move(obj* o, float dt)
{
    for (int i = 127; i > 0; i--)
    {
        o->past_positions[i] = o->past_positions[i - 1];
    }
    o->position = vect2_add(o->position, vect2_mlf(o->velocity, dt));
    o->past_positions[0] = o->position;
}

void obj_collide(obj* o1, obj* o2)
{
    printf("Wykryto zderzenie!\n");
}

float obj_mass(obj o)
{
    return o.density * o.radius * o.radius * M_PI; // density in my 2D world is: area * mass
}

float obj_force(obj o1, obj o2)
{
    return obj_mass(o1) * obj_mass(o2) / vect2_dst(o1.position, o2.position) / vect2_dst(o1.position, o2.position) * G_CONST;
}

vect2 obj_force_vect(obj o, obj interactor)
{
    return vect2_mlf(vect2_nrm(vect2_sub(interactor.position, o.position)), obj_force(interactor, o));
}
