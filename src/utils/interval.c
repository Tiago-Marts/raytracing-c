typedef struct interval {
    double min;
    double max;
} Interval;

void interval_init(Interval* i, double min, double max){
    i->min = min;
    i->max = max;
}

double interval_size(Interval* i){
    return i->max - i->min;
}

//Retorna 1 se contem e 0 caso contrário
int interval_contains(Interval* i, double x){
    return (i->min <= x && x <= i->max) ? 1 : 0;
}

//Retorna 1 se estiver aos arredores e 0 caso contrário
int interval_surrounds(Interval* i, double x){
    return (i->min < x && x < i->max) ? 1 : 0;
}