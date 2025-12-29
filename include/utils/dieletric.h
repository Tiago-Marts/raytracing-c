#ifndef DIELETRIC_H
#define DIELETRIC_H

#include "../../include/utils/color.h"
#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"


typedef struct dieletric {
    Color albedo;
    double refraction_index;
} Dieletric;

//Schilik Aprroximation 
double reflectance(double cosine, double refraction_index);


void init_dieletric(Dieletric* die, Color albedo, double refraction_index);


int scatter_dieletric( void* die_data, Ray* r_in, Vec3* point, Vec3* normal,int front_face, Color* attenuation, Ray* scattered);


#endif