#include "../include/utils/common.h"
#include "../include/utils/sphere.h"
#include "../include/utils/hittables_list_sphere.h"
#include "../include/utils/camera.h"
#include <limits.h>

int main(void) {
    //Camera
    Camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.width = 400;
    cam.samples_per_pixel = 100;

    //World 
    //NOTA: Por enquanto, tudo é feito de esferas, então há somente a lista de hits para esferas
    Hittable_List world;
    init_list(&world, 10);


    //Esfera 1
    Sphere s;
    Vec3 s_center = {0, 0, -1.0};
    sphere_init(&s, s_center, 0.5);
    add_sphere(&world, s);

    //Esfera 2
    Sphere s2;
    Vec3 s2_center = {0, -100.5, -1.0};
    sphere_init(&s2, s2_center, 100);
    add_sphere(&world, s2);

    //Esfera 3
    Sphere s3;
    Vec3 s3_center = {0.75, 0, -1.5};
    sphere_init(&s3, s3_center, 0.25);
    add_sphere(&world, s3);

    //Esfera 4
    Sphere s4;
    Vec3 s4_center = {-0.25, 0, -0.25};
    sphere_init(&s4, s4_center, 0.25);
    add_sphere(&world, s4);

    //Render
    render(&cam, &world, "image.ppm");
    free_list(&world);


    return 0;
}