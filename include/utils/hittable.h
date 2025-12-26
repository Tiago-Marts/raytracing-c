#ifndef HITTABLE_H
#define HITTABLE_H

#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"


typedef struct hittable{
    Vec3 point;
    Vec3 normal;
    double t;
    int front_face;
} Hittable; 

//O livro decide por usar uma normal que sempre aponta pra fora ao invés de sempre apontar contra o raio
void set_face_normal(Hittable* h, Ray* r, Vec3* outward_normal);



#endif