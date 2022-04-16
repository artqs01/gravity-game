#include "obj.h"
#include "vect2.h"

#include <stdio.h>

void obj_collision_check(obj* arr, int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; i++)
            if (vect2_dst(arr[i].pos, arr[j].pos) <= arr[i].r + arr[j].r)
            {
                //obj_collide(arr[i], arr[j]);
                printf("Wykryto zderzenie!\n");
            } 
}

void obj_collide(obj o1, obj o2)
{

}
