#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>

typedef struct vec3 {
    double x;
    double y;
    double z;
} Vec3;

//Inicializar um ponto
void vec3_init(Vec3* point, double x, double y, double z);

//Operações com escalar
void vec3_scalar_mult(Vec3* point, double a);


void vec3_scalar_div(Vec3* point, double a);

//Operações vetoriais
double vec3_dot_prod(Vec3* u, Vec3* v);

void vec3_cross_prod(Vec3* u, Vec3* v, Vec3* w);

void vec3_vec_add(Vec3* u, Vec3* v, Vec3* w);


void vec3_vec_sub(Vec3* u, Vec3* v, Vec3* w);

void vec3_vec_mult(Vec3* u, Vec3* v, Vec3* w);

double vec3_length(Vec3* u);

void vec3_normalize(Vec3* u);

//Funções utilitárias
void vec3_print(Vec3* u);

#endif