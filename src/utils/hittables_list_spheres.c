#include <stdlib.h>
#include "../../include/utils/hittable.h"
#include "../../include/utils/sphere.h"
#include "../../include/utils/ray.h"

typedef struct hittable_list{
    size_t index;
    size_t list_capacity;
    Sphere* list_sphere;
} Hittable_List;

void init_list(Hittable_List* h, size_t capacity){
    h->list_sphere = malloc(capacity * sizeof(Sphere));
    h->index = 0;
    h->list_capacity = capacity;
}

void free_list(Hittable_List* h){
    free(h->list_sphere);
    h->list_sphere = NULL;
    h->index = 0;
    h->list_capacity = 0;
}

void add_sphere(Hittable_List* h, Sphere object){
    if(h->index == h->list_capacity){
        h->list_capacity *= 2;
        h->list_sphere = realloc(h->list_sphere, h->list_capacity*sizeof(Sphere));
    }
    h->list_sphere[h->index++] = object;

}

void remove_hittable(Hittable_List* h, int index){
    for(int i = index; i < (int) h->list_capacity - 1; i++) h->list_sphere[i] = h->list_sphere[i+1];
    Sphere* tmp = realloc(h->list_sphere, (h->list_capacity-1) * sizeof(*h->list_sphere));

    //Se não há mais memória
    if(tmp == NULL && (int) h->list_capacity > 1) exit(EXIT_FAILURE);
    
    h->list_capacity--;
    h->index--;
    h->list_sphere = tmp;
}

int hit_list(Hittable_List* h, Ray* r, double ray_tmin, double ray_tmax, Hittable* rec){
    Hittable temp_rec;
    int hit_anything = 0;
    double closest = ray_tmax;
    for(int i = 0; i < (int) h->index; i++){
        if(hit_sphere(&(h->list_sphere[i]), r, ray_tmin, closest, &temp_rec)){
            hit_anything = 1;
            closest = temp_rec.t;
            *rec = temp_rec;
        }
    }

    return hit_anything;
}

//void print_list