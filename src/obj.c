#include "obj.h"
#include "vect2.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <math.h>
#include <stdio.h>

obj obj_create(float r, float m, vect2 p, vect2 v)
{
	obj o = {r, m, p, v, {0.0f, 0.0f}};
	for (int i = 0; i < PAST_POSITIONS_NUM; i++)
		o.past_p[i] = o.p;
	return o;
}

void obj_update(obj* arr, int size, float dt)
{
	float coll_pred_time;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j)
			{
				vect2 fg = obj_force_vect(arr[i], arr[j]);
				arr[i].dv = vect2_add(vect2_mlf(fg, 1.0f / arr[i].m), arr[i].dv);
			}
			coll_pred_time = obj_collision_prediction(&arr[i], &arr[j]);
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
		}
		arr[i].v = vect2_add(arr[i].v, vect2_mlf(arr[i].dv, dt));
		arr[i].v = vect2_mlf(arr[i].v, 1.0f - DAMPING_CONST * dt);
	}
	for (int i = 0; i < size; i++)
	{
		arr[i].dv = (vect2){0,0};
	}
}

void obj_update_wrong(obj* arr, int size, float dt)
{
	for (int i = 0; i < size; i++)
	{
		arr[i].dv = (vect2){0,0};
	}
	float coll_pred_time;
	for (int i = 0; i < size - 1; i++)
		for (int j = i + 1; j < size; j++)
		{
			vect2 fg = obj_force_vect(arr[i], arr[j]);
			arr[i].dv = vect2_mlf(fg, 1.0f / arr[i].m);
			arr[i].v = vect2_add(arr[i].v, vect2_mlf(arr[i].dv, dt));

			arr[j].dv = vect2_mlf(fg, -1.0f / arr[j].m);
			arr[j].v = vect2_add(arr[j].v, vect2_mlf(arr[j].dv, dt));
			
			coll_pred_time = obj_collision_prediction(&arr[i], &arr[j]);
			//printf("coll_pred_time = %f\n", coll_pred_time);
			draw_v(arr[i].p, vect2_mlf(arr[i].v, coll_pred_time), 1.0f, al_map_rgb(255, 0, 255));
			draw_v(arr[j].p, vect2_mlf(arr[j].v, coll_pred_time), 1.0f, al_map_rgb(255, 0, 255));
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
//tghfhfth
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
		o->past_p[i] = o->past_p[i - 1];
	}
	o->past_p[0] = o->p;
	o->p = vect2_add(o->p, vect2_mlf(o->v, dt));
}

void obj_collide(obj* o1, obj* o2)
{
	float inv_mass_sum = 1.0f / (o1->m + o2->m);
	float overlap = o1->r + o2->r - vect2_dst(o1->p, o2->p);
	if (overlap > 0)
	{
		vect2 n = vect2_nrm(vect2_sub(o1->p, o2->p));
		o1->p = vect2_add(o1->p, vect2_mlf(n, overlap * o2->m * inv_mass_sum));
		o2->p = vect2_add(o2->p, vect2_mlf(n, -overlap * o1->m * inv_mass_sum));
	}
	
	al_draw_line(o1->p.x, o1->p.y, o2->p.x, o2->p.y, al_map_rgb(0,0,255), 5.0);
	vect2 n = vect2_nrm(vect2_sub(o1->p, o2->p));
	vect2 t = vect2_rot(n, M_PI_2);
	float v1_n1 = vect2_dot(n, o1->v);
	float v1_t = vect2_dot(t, o1->v);
	float v2_n1 = vect2_dot(n, o2->v);
	float v2_t = vect2_dot(t, o2->v);

	if (v1_n1 - v2_n1 > 0)
		return;

	float v1_n2 = (o1->m * v1_n1 + o2->m * v2_n1 + o2->m * COR * (v2_n1 - v1_n1)) * inv_mass_sum;
	o1->v.x = n.x * v1_n2 + t.x * v1_t;
	o1->v.y = n.y * v1_n2 + t.y * v1_t;

	float v2_n2 = (o2->m * v2_n1 + o1->m * v1_n1 + o1->m * COR * (v1_n1 - v2_n1)) * inv_mass_sum;
	o2->v.x = n.x * v2_n2 + t.x * v2_t;
	o2->v.y = n.y * v2_n2 + t.y * v2_t;
}

float obj_force(obj o1, obj o2)
{
	float f = o1.m * o2.m / (vect2_dst(o1.p, o2.p) * vect2_dst(o1.p, o2.p)) * G_CONST;
	// if (f > 10000)
	//     return 10000.f;
	// else
		return f;
}

float obj_collision_prediction(obj* o1, obj* o2)
{
	float dvx = o1->v.x - o2->v.x;
	float dvy = o1->v.y - o2->v.y;
	float dpx = o1->p.x - o2->p.x;
	float dpy = o1->p.y - o2->p.y;
	float R_sqr = (o1->r + o2->r) * (o1->r + o2->r);
	float a = (dvx) * (dvx) + (dvy) * (dvy);
	if (a <= 0)
		return -1;
	float b = 2.f * (dvx * dpx + dvy * dpy);
	float c = dpx * dpx + dpy * dpy - R_sqr;
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
	return vect2_mlf(vect2_nrm(vect2_sub(interactor.p, o.p)), obj_force(interactor, o));
}
