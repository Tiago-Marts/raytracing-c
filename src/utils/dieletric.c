#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"
#include "../../include/utils/math_functions.h"
#include <math.h>

typedef struct dieletric {
    Color albedo;
    double refraction_index;
} Dieletric;

void init_dieletric(Dieletric* die, Color albedo, double refraction_index){
    die->albedo = albedo;
    die->refraction_index = refraction_index;
}

//Schilik Aprroximation 
double reflectance(double cosine, double refraction_index){
    double r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 *= r0;
    return r0 + (1-r0) *  pow((1-cosine), 5.0);
}


int scatter_dieletric( void* die_data, Ray* r_in, Vec3* point, Vec3* normal,int front_face, Color* attenuation, Ray* scattered){
    Dieletric* die = die_data;
    r_in = r_in;

    double ri = front_face == 1 ? (1.0/die->refraction_index) : die->refraction_index;

    Vec3 unit_direction = r_in->direction;
    vec3_normalize(&unit_direction);

    //Calculo do angulo de reflexão total
    Vec3 minus_unit_direction = unit_direction;
    vec3_scalar_mult(&minus_unit_direction, -1.0);

    double cos_theta = vec3_dot_prod(&minus_unit_direction, normal);
    cos_theta = cos_theta > 1.0 ? 1.0 : cos_theta;

    double sin_theta = sqrt(1.0 - (cos_theta*cos_theta));

    int cannot_refract = ri * sin_theta > 1.0 ? 1 : 0;
    Vec3 direction;

    if(cannot_refract || reflectance(cos_theta, ri) > random_double()){
        direction = unit_direction;
        vec3_reflect(&direction, normal);
    } else {
        vec3_refract(&direction, &unit_direction, normal, ri);
    }



    scattered->origin = *point;
    scattered->direction = direction;
    
    *attenuation = die->albedo;
    return 1;
}