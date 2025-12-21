#include "../../include/utils/vec3.h"

typedef struct ray {
    Vec3 origin;
    Vec3 direction;
} Ray;

void ray_init(Ray* r, Vec3 origin, Vec3 direction){
    r->origin = origin;
    r->direction = direction;
}

void point_at(Ray* ray, double t, Vec3* point){
    Ray r = *ray;
    vec3_scalar_mult(&(r.direction), t);
    vec3_vec_add(&(r.origin), &(r.direction), point);
}