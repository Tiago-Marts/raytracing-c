#ifndef RAY_H
#define RAY_H

#include "../../include/utils/vec3.h"

typedef struct ray {
    Vec3 origin;
    Vec3 direction;
} Ray;

void ray_init(Ray* r, Vec3 origin, Vec3 direction);

void point_at(Ray* ray, double t, Vec3* point);


#endif