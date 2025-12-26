#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"



int scatter_lambertian( Ray* r_in, Vec3* point, Vec3* normal, Color* attenuation, Ray* scattered){
    Vec3 scatter_direction;
    vec3_random_unit(&scatter_direction);
    vec3_vec_add(&scatter_direction, normal, &scatter_direction);

    if(near_zero(&scatter_direction)) scatter_direction = *normal;

    scattered->origin = *point;
    scattered->direction = scatter_direction;
    return 1;
}