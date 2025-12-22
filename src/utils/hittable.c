#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"

typedef struct hittable{
    Vec3 point;
    Vec3 normal;
    double t;
    int front_face;
} Hittable; 

//O livro decide por usar uma normal que sempre aponta pra fora ao invés de sempre apontar contra o raio
void set_face_normal(Hittable* h, Ray* r, Vec3* outward_normal){
    //NOTA: Outward normal tem que ser normalizado antes de passar como atributo
    h->front_face = 0;
    if(vec3_dot_prod(&(r->direction), outward_normal) < 0) h->front_face = 1;
    
    h->normal = *(outward_normal);

    if(h->front_face == 0){
        vec3_scalar_mult(&(h->normal), -1.0);
    }
}

