#include <stdio.h>
#include "../include/utils/vec3.h"
#include "../include/utils/color.h"

int main(void) {
    const int height = 1024;
    const int width = 1024;
    const char* output_path = "image.ppm";

    FILE *f = fopen(output_path, "wb");

    //Especificação do PPM
    fprintf(f, "P6\n");
    fprintf(f, "%d\n", width);
    fprintf(f, "%d\n", height);
    fprintf(f, "255\n");


    //Imagem Teste
    for(int y = 0; y < height ; y++){
        printf("Progresso: %d / %d \n", (y+1), height);
        for(int x = 0; x < width; x++){
            Color pixel_color;
            color_init(&pixel_color, ((double) x) / (width-1),  ((double) y) / (height - 1), 0.0);
            write_color(f, &pixel_color);
        }
    }

    fclose(f);



    return 0;
}