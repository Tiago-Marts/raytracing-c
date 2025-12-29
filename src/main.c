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
    cam.width = 800;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;
    cam.vfov = 40;

    Vec3 look_from = {10, 0.3,2};
    Vec3 look_at = {0,0,0};
    Vec3 v_up = {0, 1, 0};
    
    cam.look_from = look_from;
    cam.look_at = look_at;
    cam.v_up = v_up;

    cam.defocus_angle = 1.3;
    cam.focus_dist = 10;

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
    Color ground_color = {0.1, 0.1, 0.1};
    init_lambertian(&ground, ground_color);

    Material ground_material;
    init_material(&ground_material, &ground, &scatter_lambertian);


    //Metal da esfera esquerda
    Metal metal_left;
    Color metal_left_col = {0.9, 0.6, 0.6};
    init_metal(&metal_left, metal_left_col, 0.0);

    Material material_left;
    init_material(&material_left, &metal_left, &scatter_metal);


    //Metal da esfera direita
    Metal metal_right;
    Color metal_right_col = {0.8, 0.6, 0.2};
    init_metal(&metal_right, metal_right_col, 0.1);

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
    Color air_col = {0.9,0.9,1.0};
    init_dieletric(&die_air, air_col, 1.0/1.50);

    Material dieletric_air_material;
    init_material(&dieletric_air_material, &die_air, &scatter_dieletric);

    //Esfera Centro
    Sphere s;
    Vec3 s_center = {0, 0.5, 0};
    sphere_init(&s, s_center, 1.0, center_material);
    add_sphere(&world, s);

    Sphere s_m;
    Vec3 sm_center = {-1.8, 0, -1.8};
    sphere_init(&s_m, sm_center, 0.5, material_left);
    add_sphere(&world, s_m);

    Sphere s_n;
    Vec3 sn_center = {1.8, 0, 1.8};
    sphere_init(&s_n, sn_center, 0.5, material_left);
    add_sphere(&world, s_n);

    //Esfera que age como chão
    Sphere s2;
    Vec3 s2_center = {0, -100.5, -1.0};
    sphere_init(&s2, s2_center, 100, ground_material);
    add_sphere(&world, s2);

    //Esfera da esquerda (vidro)
    Sphere s3;
    Vec3 s3_center = {8, 0.6, 0};
    sphere_init(&s3, s3_center, 1.2, dieletric_material);
    add_sphere(&world, s3);

    //Esfera da esquerda (ar)
    Sphere s3_air;
    sphere_init(&s3_air, s3_center, 1.0, dieletric_air_material);
    add_sphere(&world, s3_air);


    //Esfera da direita
    Sphere s4;
    Vec3 s4_center = {5, 0.0, -0.5};
    sphere_init(&s4, s4_center, 0.5, material_right);
    add_sphere(&world, s4);

    //Esfera do fundo
    Sphere s5;
    Vec3 s5_center = {-3, 0.0, -5};
    sphere_init(&s5, s5_center, 0.5, center_material);
    add_sphere(&world, s5);


    //Render
    render(&cam, &world, "image.ppm");
    free_list(&world);


    return 0;
}