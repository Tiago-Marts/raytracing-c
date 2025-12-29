#include "../include/utils/common.h"
#include "../include/utils/sphere.h"
#include "../include/utils/lambertian.h"
#include "../include/utils/metal.h"
#include "../include/utils/dieletric.h"
#include "../include/utils/material.h"
#include "../include/utils/hittables_list_sphere.h"
#include "../include/utils/camera.h"
#include <limits.h>

int main(void) {
    //Camera
    Camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    //World 
    //NOTA: Por enquanto, tudo é feito de esferas, então há somente a lista de hits para esferas
    Hittable_List world;
    init_list(&world, 10);


    //Material Difuso
    Lambertian center_sphere;
    Color center_color = {0.1, 0.2, 0.5};
    init_lambertian(&center_sphere, center_color);

    Material center_material;
    init_material(&center_material, &center_sphere, &scatter_lambertian);


    //Material Chão
    Lambertian ground;
    Color ground_color = {0.8, 0.8, 0.0};
    init_lambertian(&ground, ground_color);

    Material ground_material;
    init_material(&ground_material, &ground, &scatter_lambertian);


    //Metal da esfera esquerda
    Metal metal_left;
    Color metal_left_col = {0.8, 0.8, 0.8};
    init_metal(&metal_left, metal_left_col, 0.3);

    Material material_left;
    init_material(&material_left, &metal_left, &scatter_metal);


    //Metal da esfera direita
    Metal metal_right;
    Color metal_right_col = {0.8, 0.6, 0.2};
    init_metal(&metal_right, metal_right_col, 1.0);

    Material material_right;
    init_material(&material_right, &metal_right, &scatter_metal);

    //Dieletrico (Vidro)
    Dieletric die_left;
    Color die_col = {1.0, 1.0, 1.0};
    init_dieletric(&die_left, die_col, 1.50);

    Material dieletric_material;
    init_material(&dieletric_material, &die_left, &scatter_dieletric);

    //Dieletrico (Ar para vidro)
    Dieletric die_air;
    Color air_col = {1.0,1.0,1.0};
    init_dieletric(&die_air, air_col, 1.0/1.50);

    Material dieletric_air_material;
    init_material(&dieletric_air_material, &die_air, &scatter_dieletric);

    //Esfera Centro
    Sphere s;
    Vec3 s_center = {0, 0, -1.2};
    sphere_init(&s, s_center, 0.5, center_material);
    add_sphere(&world, s);

    //Esfera que age como chão
    Sphere s2;
    Vec3 s2_center = {0, -100.5, -1.0};
    sphere_init(&s2, s2_center, 100, ground_material);
    add_sphere(&world, s2);

    //Esfera da esquerda (vidro)
    Sphere s3;
    Vec3 s3_center = {-1.0, 0.0, -1.0};
    sphere_init(&s3, s3_center, 0.5, dieletric_material);
    add_sphere(&world, s3);

    //Esfera da esquerda (ar)
    Sphere s3_air;
    sphere_init(&s3_air, s3_center, 0.4, dieletric_air_material);
    add_sphere(&world, s3_air);


    //Esfera da direita
    Sphere s4;
    Vec3 s4_center = {1.0, 0.0, -1.0};
    sphere_init(&s4, s4_center, 0.5, material_right);
    add_sphere(&world, s4);


    //Render
    render(&cam, &world, "image.ppm");
    free_list(&world);


    return 0;
}