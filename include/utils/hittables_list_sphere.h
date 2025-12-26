#ifndef HITTABLES_LIST_H
#define HITTABLES_LIST_H

#include <stdlib.h>
#include "../../include/utils/hittable.h"
#include "../../include/utils/sphere.h"
#include "../../include/utils/ray.h"
#include "../../include/utils/interval.h"
#include "../../include/utils/material.h"

typedef struct hittable_list{
    size_t list_size;
    size_t list_capacity;
    Sphere* list_sphere;
} Hittable_List;

void init_list(Hittable_List* h, size_t capacity);

void free_list(Hittable_List* h);


void add_sphere(Hittable_List* h, Sphere object);

void remove_hittable(Hittable_List* h, int index);

int hit_list(Hittable_List* h, Ray* r, Interval* ray_t, Hittable* rec, Material* hit_material);
//void print_list

#endif