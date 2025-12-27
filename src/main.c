#include "../include/utils/common.h"
#include "../include/utils/sphere.h"
#include "../include/utils/material.h"
#include "../include/utils/hittables_list_sphere.h"
#include "../include/utils/camera.h"
#include <limits.h>

int main(void) {
    //Camera
    Camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.width = 600;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    //World 
    //NOTA: Por enquanto, tudo é feito de esferas, então há somente a lista de hits para esferas
    Hittable_List world;
    init_list(&world, 10);


    //Material Difuso
    Material lambertian;
    Color lambertian_col = {0.2, 0.7, 0.5};
    init_material(&lambertian, "dif", lambertian_col );

    //Material Chão
    Material ground;
    Color ground_col = {0.2, 0.2, 0.2};
    init_material(&ground, "dif", ground_col );

    //Metal Amarelo
    Material metal_right;
    Color metal_yellow = {0.8, 0.6, 0.2};
    init_material(&metal_right, "metal", metal_yellow);

    //Metal sem cor
    Material metal_left;
    Color metal_white = {0.8, 0.8, 0.8};
    init_material(&metal_left, "metal", metal_white);

    //Esfera Centro
    Sphere s;
    Vec3 s_center = {0, 0, -1.2};
    sphere_init(&s, s_center, 0.5, lambertian);
    add_sphere(&world, s);

    //Esfera que age como chão
    Sphere s2;
    Vec3 s2_center = {0, -100.5, -1.0};
    sphere_init(&s2, s2_center, 100, ground);
    add_sphere(&world, s2);

    //Esfera Esquerda
    Sphere s3;
    Vec3 s3_center = {-1.0, 0, -1.0};
    sphere_init(&s3, s3_center, 0.5, metal_left);
    add_sphere(&world, s3);

    //Esfera Direita
    Sphere s4;
    Vec3 s4_center = {1.0, 0, -1.0};
    sphere_init(&s4, s4_center, 0.5, metal_right);
    add_sphere(&world, s4);

    //Render
    render(&cam, &world, "image.ppm");
    free_list(&world);


    return 0;
}