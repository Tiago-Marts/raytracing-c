#ifndef METAL_H
#define METAL_H

#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"

int scatter_metal( Ray* r_in, Vec3* point, Vec3* normal, Color* attenuation, Ray* scattered);

#endif