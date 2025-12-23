#include <stdio.h>
#include "../../include/utils/interval.h"

typedef struct color {
    double r;
    double g;
    double b;
} Color;

void color_init(Color* col, double r, double g, double b){
    col->r = r;
    col->g = g;
    col->b = b;
}

void write_color(FILE* f, Color* col){
    Interval intensity;
    interval_init(&intensity, 0.000, 0.999);


    int r_byte = (int)(256 * clamp(&intensity, col->r));
    int g_byte = (int)(256 * clamp(&intensity, col->g));
    int b_byte = (int)(256 * clamp(&intensity, col->b));

    fputc(r_byte, f);
    fputc(g_byte, f);
    fputc(b_byte, f);
}
