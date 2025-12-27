#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"

int scatter_metal( Ray* r_in, Vec3* point, Vec3* normal, Color* attenuation, Ray* scattered){
    Vec3 reflected = r_in->direction;
    vec3_reflect(&reflected, normal);
    scattered->origin = *point;
    scattered->direction = reflected;
    return 1;
}