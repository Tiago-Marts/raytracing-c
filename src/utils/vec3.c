#include <stdio.h>
#include <math.h>

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

//Funções utilitárias
void vec3_print(Vec3* u){
    printf("%f, %f, %f", u->x, u->y, u->z);
}

