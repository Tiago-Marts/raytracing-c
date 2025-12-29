#ifndef METAL_H
#define METAL_H

#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"

typedef struct metal {
    Color albedo;
    double fuzz;
} Metal;

void init_metal(Metal* met, Color albedo, double fuzz);

int scatter_metal(void* metal_data, Ray* r_in, Vec3* point, Vec3* normal,int front_face, Color* attenuation, Ray* scattered);

#endif