#include <stdio.h>
#include <math.h>
#include "../../include/utils/math_functions.h"

typedef struct vec3 {
    double x;
    double y;
    double z;
} Vec3;



//Inicializar um ponto
void vec3_init(Vec3* point, double x, double y, double z){
    point->x = x;
    point->y = y;
    point->z = z;
}

//Operações com escalar
void vec3_scalar_mult(Vec3* point, double a){
    point->x *= a;
    point->y *= a;
    point->z *= a;
}

void vec3_scalar_div(Vec3* point, double a){
    point->x *= (1.0/a);
    point->y *= (1.0/a);
    point->z *= (1.0/a);
}

void vec3_scalar_add(Vec3 *point, double a){
    point->x += a;
    point->y += a;
    point->z += a;
}

//Operações vetoriais
double vec3_dot_prod(Vec3* u, Vec3* v) {
    return u->x * v->x + u->y * v->y + u->z * v->z;
}

void vec3_cross_prod(Vec3* u, Vec3* v, Vec3* w){
    w->x = u->y * v->z - u->z * v->y ;
    w->y = u->z * v->x - u->x * v->z;
    w->z = u->x * v->y - u->y * v->x;
}

void vec3_vec_add(Vec3* u, Vec3* v, Vec3* w){
    w->x = u->x + v->x;
    w->y = u->y + v->y;
    w->z = u->z + v->z;
}

void vec3_vec_sub(Vec3* u, Vec3* v, Vec3* w){
    w->x = u->x - v->x;
    w->y = u->y - v->y;
    w->z = u->z - v->z;
}

void vec3_vec_mult(Vec3* u, Vec3* v, Vec3* w){
    w->x = u->x * v->x;
    w->y = u->y * v->y;
    w->z = u->z * v->z;
}

double vec3_lenght_squared(Vec3* u){
    return (u->x * u->x) + (u->y * u->y) + (u->z * u->z);
}

double vec3_length(Vec3* u){
    return sqrt(vec3_lenght_squared(u));
}

void vec3_normalize(Vec3* u){
    vec3_scalar_div(u, vec3_length(u));
}

void vec3_random(Vec3* u){
    u->x = random_double();
    u->y = random_double();
    u->z = random_double();
}

void vec3_random_minmax(Vec3* u, double min, double max){
    u->x = random_double_minmax(min, max);
    u->y = random_double_minmax(min, max);
    u->z = random_double_minmax(min, max);
}

//Metodo da rejeição para escolha de um vetor unitário
void vec3_random_unit(Vec3* u){
    while(1){
        vec3_random_minmax(u, -1.0, 1.0);
        double lensq = vec3_lenght_squared(u);

        //Para lidar com imprecisão de floats
        if(1e-160 < lensq && lensq <= 1){
            vec3_scalar_div(u, lensq);
            return;
        }
    }
}

//Escolha de um vetor em um hemisfério de raio 1
void vec3_random_hemisphere(Vec3* u, Vec3* normal){
    Vec3 on_unit_sphere;
    vec3_random_unit(&on_unit_sphere);

    *u = on_unit_sphere;
    if(vec3_dot_prod(&on_unit_sphere, normal) < 0.0) {
        vec3_scalar_mult(u, -1.0);
    } 
        
}

//Retorna 1 se o vetor está proximo de 0 em todas as dimensões
int near_zero(Vec3* u){
    double s = 1e-8;
    if(u->x < s && u->y < s) {
        if(u->z < s) {
            return 1;
        }
        return 0;
    } else {
        return 0;
    }
}

//Reflete o vetor no ponto n
void vec3_reflect(Vec3* v, Vec3* n){
    Vec3 projection = *n;
    double b = 2 * vec3_dot_prod(v, n);
    vec3_scalar_mult(&projection, b);
    vec3_vec_sub(v, &projection, v);
}

//Funções utilitárias
void vec3_print(Vec3* u){
    printf("%f, %f, %f", u->x, u->y, u->z);
}



