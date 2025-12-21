#include <stdio.h>

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
    int r_byte = (int)(255.999 * col->r);
    int g_byte = (int)(255.999 * col->g);
    int b_byte = (int)(255.999 * col->b);

    fputc(r_byte, f);
    fputc(g_byte, f);
    fputc(b_byte, f);
}
