#ifndef SPHERE_H
#define SPHERE_H

#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"
#include "../../include/utils/hittable.h"
#include <math.h>

typedef struct sphere{
    Vec3 center;
    double radius;
} Sphere;

void sphere_init(Sphere* sphere, Vec3 center, double radius);

int hit_sphere(Sphere* sphere, Ray* r, double ray_tmin, double ray_tmax, Hittable* rec);

#endif