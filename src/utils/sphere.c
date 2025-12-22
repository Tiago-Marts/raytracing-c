#include "../../include/utils/vec3.h"
#include "../../include/utils/ray.h"
#include "../../include/utils/hittable.h"
#include <math.h>

typedef struct sphere{
    Vec3 center;
    double radius;
} Sphere;


void sphere_init(Sphere* sphere, Vec3 center, double radius){
    sphere->center = center;
    sphere->radius = radius;
}

int hit_sphere(Sphere* sphere, Ray* r, double ray_tmin, double ray_tmax, Hittable* rec) {
    int hitted = 1;
    Vec3 oc;
    Vec3 center = sphere->center;
    vec3_vec_sub(&center, &(r->origin), &oc);
    double a = vec3_lenght_squared(&(r->direction));
    double b = vec3_dot_prod(&(r->direction), &oc);
    double radius = sphere->radius;
    double c = vec3_lenght_squared(&oc) - radius*radius;
    double discriminant = b*b - a*c;

    if(discriminant < 0) hitted = 0;

    double sqrt_discriminant = sqrt(discriminant);

    //Acha a raiz que está num limite aceitável (entre o ray_tmin e ray_tmax)
    double root = (b - sqrt_discriminant) / (a);
    if(root <= ray_tmin || ray_tmax <= root){
        root = (b + sqrt_discriminant) / (a);
        if(root <= ray_tmin || ray_tmax <= root) {
            hitted = 0;
        }
    }

    rec->t = root;
    Vec3 p;
    point_at(r, rec->t, &p);
    rec->point = p;
    Vec3 outward_normal;
    vec3_vec_sub(&(rec->point), &(sphere->center), &outward_normal);
    vec3_scalar_div(&outward_normal, sphere->radius);
    set_face_normal(rec, r, &outward_normal);
    
    return hitted;
}