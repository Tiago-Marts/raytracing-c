#ifndef INTERVAL_H
#define INTERVAL_H

typedef struct interval {
    double min;
    double max;
} Interval;

void interval_init(Interval* i, double min, double max);

double interval_size(Interval* i);

//Retorna 1 se contem e 0 caso contrário
int interval_contains(Interval* i, double x);

//Retorna 1 se estiver aos arredores e 0 caso contrário
int interval_surrounds(Interval* i, double x);
#endif