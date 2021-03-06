#include "obj.h"
#include "vect2.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <math.h>
#include <stdio.h>

obj obj_create(float r, float m, float q, vect2 p, vect2 v)
{
	obj o = {r, m, q, p, v, {0.0f, 0.0f}};
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
				vect2 fg = obj_force_vect(&arr[i], &arr[j], obj_gravity_force_value);
				arr[i].dv = vect2_add(vect2_mlf(fg, 1.0f / arr[i].m), arr[i].dv);
				vect2 fc = obj_force_vect(&arr[i], &arr[j], obj_coulomb_force_value);
				arr[i].dv = vect2_add(vect2_mlf(fc, 1.0f / arr[i].m), arr[i].dv);
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
		arr[i].dv = (vect2){0,0};
	}
}

void obj_move(obj* o, float dt)
{
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
	
	al_draw_line(o1->p.x, o1->p.y, o2->p.x, o2->p.y, al_map_rgb(0, 0, 255), 5.0f);
	al_draw_line(o1->p.x, o1->p.y, o2->p.x, o2->p.y, al_map_rgb(200, 200, 200), 0.3f);
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

	float avg_q = (o1->q + o2->q) * 0.5f;
	o1->q = avg_q;
	o2->q = avg_q;
}

float obj_gravity_force_value(const obj* o1, const obj* o2)
{
	float f = o1->m * o2->m / (vect2_dst(o1->p, o2->p) * vect2_dst(o1->p, o2->p)) * G_CONST;
		return f;
}

float obj_coulomb_force_value(const obj* o1, const obj* o2)
{
	float f = o1->q * (-o2->q) / (vect2_dst(o1->p, o2->p) * vect2_dst(o1->p, o2->p)) * K_CONST;
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

vect2 obj_force_vect(const obj* o, const obj* interactor, float(*value)(const obj*, const obj*))
{
	return vect2_mlf(vect2_nrm(vect2_sub(interactor->p, o->p)), value(interactor, o));
}
