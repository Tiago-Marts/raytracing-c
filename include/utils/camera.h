#ifndef CAMERA_H
#define CAMERA_H


#include "../../include/utils/hittable.h"
#include "../../include/utils/color.h"
#include "../../include/utils/interval.h"
#include "../../include/utils/hittables_list_sphere.h"
#include <stdio.h>

typedef struct camera {
    int width;
    int height;
    double aspect_ratio;
    int image_height;
    Vec3 center;
    Vec3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
} Camera;

//Camera
void camera_initialize(Camera* cam);

void render(Camera* cam, Hittable_List* world, const char* path);


#endif