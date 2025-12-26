#include "../../include/utils/color.h"
#include "../../include/utils/ray.h"
#include "../../include/utils/lambertian.h"
#include <string.h>

typedef int (*scatter_func)(Ray* , Vec3*, Vec3*, Color*, Ray*);

typedef struct material {
    const char* tipo;
    Color albedo;
    scatter_func scatter;
} Material;



scatter_func define_material(const char* tipo){
    scatter_func func_ptr;

    if(strcmp(tipo, "dif") == 0){
        func_ptr = &scatter_lambertian;
    }

    return func_ptr;
}


void init_material(Material* mat, const char* tipo, Color albedo){

    mat->tipo = tipo;
    mat->albedo = albedo;
    mat->scatter = define_material(tipo);

}
