#ifndef RTWEEKEND_H
#define RTWEEKEND_H

//Bibliotecas Padrão do C
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//Arquivos headers do projeto
#include "../../include/utils/color.h"
#include "../../include/utils/ray.h"
#include "../../include/utils/interval.h"
#include "../../include/utils/vec3.h"

//Funções
double degrees_to_radians(double degrees);


double lerp(double start, double end, double t);

#endif