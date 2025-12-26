#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"


int scatter_lambertian(Ray* r_in, Vec3* point, Vec3* normal, Color* attenuation, Ray* scattered);

#endif