#include <stdio.h>

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
        for(int x = 0; x < width; x++){
            double r = ((double) x) / (width - 1);
            double g = ((double) y) / (height - 1);
            double b = 0.0;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);

            fputc(ir, f);
            fputc(ig, f);
            fputc(ib, f);
        }
    }

    fclose(f);

    return 0;
}