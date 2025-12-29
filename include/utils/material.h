#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../include/utils/color.h"
#include "../../include/utils/ray.h"


#include "../../include/utils/color.h"
#include "../../include/utils/ray.h"


typedef int (*scatter_func)(void*, Ray* , Vec3*, Vec3*, int, Color*, Ray* );

typedef struct material {
    scatter_func scatter;
    void* material_data;
} Material;

void init_material(Material* mat, void* material_data, scatter_func scatter_light);


#endif