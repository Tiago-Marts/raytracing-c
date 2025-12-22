//Bibliotecas Padrão do C
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//Arquivos headers do projeto
#include "../../include/utils/color.h"
#include "../../include/utils/ray.h"
#include "../../include/utils/vec3.h"

//Constants
const double pi = 3.1415926535897932385;

//Funções
double degrees_to_radians(double degrees){
    return degrees*pi / 180.0;
}

double lerp(double start, double end, double t){
    return (1-t)*start + end*t;
}

