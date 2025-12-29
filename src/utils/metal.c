#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"


typedef struct metal {
    Color albedo;
    double fuzz;
} Metal;

void init_metal(Metal* met, Color albedo, double fuzz){
    met->albedo = albedo;
    met->fuzz = fuzz;
}

int scatter_metal(void* metal_data, Ray* r_in, Vec3* point, Vec3* normal, int front_face, Color* attenuation, Ray* scattered){
    
    Metal* met = metal_data;
    double fuzz = met->fuzz;
    
    if(fuzz > 1) fuzz = 1;

    
    Vec3 reflected = r_in->direction;
    vec3_reflect(&reflected, normal);
    Vec3 temp_vector = reflected;
    vec3_normalize(&temp_vector);

    Vec3 fuzz_vector;
    vec3_random_unit(&fuzz_vector);
    vec3_scalar_mult(&fuzz_vector, fuzz);
    
    vec3_vec_add(&temp_vector, &fuzz_vector, &reflected);


    scattered->origin = *point;
    scattered->direction = reflected;


    *attenuation =  met->albedo;

    double dot = vec3_dot_prod(&(scattered->direction), normal);

    return dot > 0 ? 1 : 0;
}