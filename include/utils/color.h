#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include "../../include/utils/interval.h"

typedef struct color {
    double r;
    double g;
    double b;
} Color;

void color_init(Color* col, double r, double g, double b);

void write_color(FILE* f, Color* col);

#endif