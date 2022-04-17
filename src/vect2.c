#include "vect2.h"

#include <math.h>

vect2 vect2_add(vect2 v1, vect2 v2)
{
    return (vect2){v1.x + v2.x, v1.y + v2.y};
}

vect2 vect2_rot(vect2 v1, vect2 center, float angle)
{
    return vect2_add(center,
        (vect2)
        {
            (v1.x - center.x) * cos(angle) - (v1.y - center.y) * sin(angle),
            (v1.x - center.x) * sin(angle) + (v1.y - center.y) * cos(angle)
        });
}

vect2 vect2_mlf(vect2 v, float f)
{
    return (vect2){v.x * f, v.y * f};
}

vect2 vect2_neg(vect2 v)
{
    return (vect2){-v.x, -v.y};
}

vect2 vect2_sub(vect2 v, vect2 subtractor)
{
    return vect2_add(v, vect2_neg(subtractor));
}

vect2 vect2_nrm(vect2 v)
{
    return vect2_mlf(v, 1 / vect2_len(v));
}

float vect2_dot(vect2 v1, vect2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float vect2_det(vect2 v1, vect2 v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

float vect2_len(vect2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

float vect2_dst(vect2 v1, vect2 v2)
{
    return vect2_len(vect2_sub(v1, v2));
}
