//Bibliotecas Padrão do C
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//Arquivos headers do projeto
#include "../../include/utils/color.h"
#include "../../include/utils/ray.h"
#include "../../include/utils/interval.h"
#include "../../include/utils/vec3.h"

//Constants
const double pi = 3.1415926535897932385;

//Funções
double degrees_to_radians(double degrees){
    return degrees*pi / 180.0;
}

//Retorna um valor entre o start e end com base no valor de t
double lerp(double start, double end, double t){
    return (1-t)*start + end*t;
}

//Retorna um valor real aleatório entre [0,1)
double random_double(){
    return rand() / (RAND_MAX + 1.0);
}

//Retorna um valor real aleatório entre [min, max)
double random_double_minmax(double min, double max){
    return min + (max-min) * random_double();
}

