#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"

typedef struct lambertian {
    Color albedo;
} Lambertian;

void init_lambertian(Lambertian* lamb, Color albedo);

int scatter_lambertian( void* lambertian_data, Ray* r_in, Vec3* point, Vec3* normal,int front_face, Color* attenuation, Ray* scattered);

#endif