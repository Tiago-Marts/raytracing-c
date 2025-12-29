#include <stdlib.h>



//Retorna um valor real aleatório entre [0,1)
double random_double(){
    return rand() / (RAND_MAX + 1.0);
}

//Retorna um valor real aleatório entre [min, max)
double random_double_minmax(double min, double max){
    return min + (max-min) * random_double();
}