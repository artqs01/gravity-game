#include "obj.h"
#include "vect2.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <math.h>
#include <stdio.h>

void obj_update(obj* arr, int size, float dt)
{
    for (int i = 0; i < size; i++)
    {
        arr[i].acceleration = (vect2){0,0};
    }
    float coll_pred_time;
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
        {
            vect2 fg = obj_force_vect(arr[i], arr[j]);
            arr[i].acceleration = vect2_mlf(fg, 1.0f / arr[i].mass);
            arr[i].velocity = vect2_add(arr[i].velocity, vect2_mlf(arr[i].acceleration, dt));

            arr[j].acceleration = vect2_mlf(fg, -1.0f / arr[j].mass);
            arr[j].velocity = vect2_add(arr[j].velocity, vect2_mlf(arr[j].acceleration, dt));
            
            coll_pred_time = obj_collision_prediction(&arr[i], &arr[j], dt);
            //printf("coll_pred_time = %f\n", coll_pred_time);
            draw_v(arr[i].position, vect2_mlf(arr[i].velocity, coll_pred_time), 1.0f, al_map_rgb(255, 0, 255));
            draw_v(arr[j].position, vect2_mlf(arr[j].velocity, coll_pred_time), 1.0f, al_map_rgb(255, 0, 255));
            if (coll_pred_time >= 0 && coll_pred_time < dt)
            {
                //printf("Przewidziano zderzenie, coll_pred_time = %f\n", coll_pred_time);
                obj_move(&arr[i], coll_pred_time);
                obj_move(&arr[j], coll_pred_time);
                obj_collide(&arr[i], &arr[j]);
                obj_move(&arr[i], dt - coll_pred_time);
                obj_move(&arr[j], dt - coll_pred_time);
            }
            else
            {
                obj_move(&arr[i], dt);
                obj_move(&arr[j], dt);
            }
            // if (vect2_dst(arr[i].position, arr[j].position) <= arr[i].radius + arr[j].radius)
            // {
            //     printf("Wykryto zderzenie, dst = %f\n", vect2_dst(arr[i].position, arr[j].position));
            //     obj_collide(&arr[i], &arr[j]);
            // }
            // obj_move(&arr[i], dt);
            // obj_move(&arr[j], dt);
        }
}
//vect2_dst(arr[i].position, arr[j].position) <= arr[i].radius + arr[j].radius

// void obj_interact(obj* o1, obj* o2, float dt)
// {
//     vect2 f = vect2_mlf(vec);
//     draw_v(o1->position, acceleration, 10.0, al_map_rgb(0, 255, 0));
//     draw_v(o2->position, vect2_neg(acceleration), 10.0, al_map_rgb(0, 255, 0));
//     o1->velocity = vect2_add(o1->velocity, vect2_mlf(vect2_mlf(obj_force_vect(*o1, *o2), 1 / o1->mass), dt));
//     o2->velocity = vect2_add(o2->velocity, vect2_mlf(vect2_mlf(obj_force_vect(*o2, *o1), 1 / o2->mass), dt));
// }

void obj_move(obj* o, float dt)
{
    for (int i = PAST_POSITIONS_NUM - 1; i > 0; i--)
    {
        o->past_positions[i] = o->past_positions[i - 1];
    }
    o->past_positions[0] = o->position;
    o->position = vect2_add(o->position, vect2_mlf(o->velocity, dt));
}

void obj_collide(obj* o1, obj* o2)
{
    float overlap = o1->radius + o2->radius - vect2_dst(o1->position, o2->position);
    if (overlap > 0)
    {
        vect2 n = vect2_nrm(vect2_sub(o1->position, o2->position));
        o1->position = vect2_add(o1->position, vect2_mlf(n, overlap * o2->mass / (o1->mass + o2->mass)));
        o2->position = vect2_add(o2->position, vect2_mlf(n, -overlap * o1->mass / (o1->mass + o2->mass)));
    }
    
    al_draw_line(o1->position.x, o1->position.y, o2->position.x, o2->position.y, al_map_rgb(0,0,255), 5.0);
    vect2 n = vect2_nrm(vect2_sub(o1->position, o2->position));
    vect2 t = vect2_rot(n, M_PI_2);
    float v1_n1 = vect2_dot(n, o1->velocity);
    float v1_t = vect2_dot(t, o1->velocity);
    float v2_n1 = vect2_dot(n, o2->velocity);
    float v2_t = vect2_dot(t, o2->velocity);

    float v1_n2 = (o1->mass * v1_n1 + o2->mass * v2_n1 + o2->mass * COR * (v2_n1 - v1_n1)) / (o1->mass + o2->mass);
    o1->velocity.x = n.x * v1_n2 + t.x * v1_t;
    o1->velocity.y = n.y * v1_n2 + t.y * v1_t;

    float v2_n2 = (o2->mass * v2_n1 + o1->mass * v1_n1 + o1->mass * COR * (v1_n1 - v2_n1)) / (o1->mass + o2->mass);
    o2->velocity.x = n.x * v2_n2 + t.x * v2_t;
    o2->velocity.y = n.y * v2_n2 + t.y * v2_t;
}

float obj_force(obj o1, obj o2)
{
    float f = o1.mass * o2.mass / vect2_dst(o1.position, o2.position) / vect2_dst(o1.position, o2.position) * G_CONST;
    // if (f > 10000)
    //     return 10000.f;
    // else
        return f;
}

float obj_collision_prediction(obj* o1, obj* o2, float dt)
{
    float a = (o1->velocity.x - o2->velocity.x) * (o1->velocity.x - o2->velocity.x) +
              (o1->velocity.y - o2->velocity.y) * (o1->velocity.y - o2->velocity.y);
    if (a <= 0)
        return -1;
    float b = 2.f * ((o1->velocity.x - o2->velocity.x) * (o1->position.x - o2->position.x) +
                     (o1->velocity.y - o2->velocity.y) * (o1->position.y - o2->position.y));
    float c = (o1->position.x - o2->position.x) * (o1->position.x - o2->position.x) +
              (o1->position.y - o2->position.y) * (o1->position.y - o2->position.y) -
              (o1->radius + o2->radius) * (o1->radius + o2->radius);
    if (c <= 0)
        return 0;
    float delta = b * b - 4.f * a * c;
    if (delta < 0)
        return -1;
    float t1 = 0.5f * -(b + sqrtf(delta)) / a;
    return t1;
}

vect2 obj_force_vect(obj o, obj interactor)
{
    return vect2_mlf(vect2_nrm(vect2_sub(interactor.position, o.position)), obj_force(interactor, o));
}
