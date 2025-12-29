#ifndef CAMERA_H
#define CAMERA_H

#include "../../include/utils/common.h"
#include "../../include/utils/hittable.h"
#include "../../include/utils/color.h"
#include "../../include/utils/interval.h"
#include "../../include/utils/hittables_list_sphere.h"
#include <stdio.h>

typedef struct camera {
    int samples_per_pixel;
    double pixel_samples_scale;
    int max_depth;
    int width;
    int height;
    double aspect_ratio;
    int image_height;

    double vfov;
    Vec3 look_from;
    Vec3 look_at;
    Vec3 v_up;

    double defocus_angle;
    double focus_dist;

    Vec3 center;
    Vec3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
    Vec3 u, v, w; // Base ortonormal da camera
    Vec3 defocus_disk_u;
    Vec3 defocus_disk_v;
} Camera;

//Constroi um vetor dentro de um quadrado unitário, apontando pra uma direação qualquer nesse quadrado
void sample_square(Vec3* v);

//Constroi o disco de desfoque
void defocus_disk_sample(Vec3* point, Vec3 center, Vec3 defocus_u, Vec3 defocus_v);

//Constroi um raio saindo da origem da camera em direção a um ponto aleatório próximo de (i,j)
void get_ray(Ray* r, Camera* cam, int i, int j);

//Camera
void camera_initialize(Camera* cam);

void render(Camera* cam, Hittable_List* world, const char* path);


#endif