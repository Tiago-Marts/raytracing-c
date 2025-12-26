#include <stdio.h>
#include "../../include/utils/interval.h"
#include <math.h>

typedef struct color {
    double r;
    double g;
    double b;
} Color;

double linear_to_gamma(double linear_component){
    if(linear_component > 0.0) return sqrt(linear_component);

    return 0.0;
}

void color_init(Color* col, double r, double g, double b){
    col->r = r;
    col->g = g;
    col->b = b;
}

void write_color(FILE* f, Color* col){
    Interval intensity;
    interval_init(&intensity, 0.000, 0.999);

    //Cor linear para o espaço Gamma 2
    double r = linear_to_gamma(col->r);
    double g = linear_to_gamma(col->g);
    double b = linear_to_gamma(col->b);

    int r_byte = (int)(256 * clamp(&intensity, r));
    int g_byte = (int)(256 * clamp(&intensity, g));
    int b_byte = (int)(256 * clamp(&intensity, b));

    fputc(r_byte, f);
    fputc(g_byte, f);
    fputc(b_byte, f);
}
