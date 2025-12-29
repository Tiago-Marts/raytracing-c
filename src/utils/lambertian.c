#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"


typedef struct lambertian {
    Color albedo;
} Lambertian;


void init_lambertian(Lambertian* lamb, Color albedo){
    lamb->albedo = albedo;
}

int scatter_lambertian( void* lambertian_data, Ray* r_in, Vec3* point, Vec3* normal, int front_face, Color* attenuation, Ray* scattered){
    Lambertian* material = lambertian_data;
    *attenuation = material->albedo;



    Vec3 scatter_direction;
    vec3_random_unit(&scatter_direction);
    vec3_vec_add(&scatter_direction, normal, &scatter_direction);

    if(near_zero(&scatter_direction)) scatter_direction = *normal;

    scattered->origin = *point;
    scattered->direction = scatter_direction;
    return 1;
}