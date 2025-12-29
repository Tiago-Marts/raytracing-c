#include "../../include/utils/common.h"
#include "../../include/utils/hittable.h"
#include "../../include/utils/color.h"
#include "../../include/utils/interval.h"
#include "../../include/utils/hittables_list_sphere.h"
#include <time.h>
#include <stdio.h>

typedef struct camera {
    int samples_per_pixel;
    double pixel_samples_scale;
    int max_depth;
    int width;
    int height;
    double aspect_ratio;
    int image_height;
    Vec3 center;
    Vec3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
} Camera;

//Constroi um vetor dentro de um quadrado unitário, apontando pra uma direação qualquer nesse quadrado
void sample_square(Vec3* v){
    double x = random_double() - 0.5;
    double y = random_double() - 0.5;

    v->x = x;
    v->y = y;
    v->z = 0.0;
}

//Constroi um raio saindo da origem da camera em direção a um ponto aleatório próximo de (i,j)
void get_ray(Ray* r, Camera* cam, int i, int j){
    Vec3 offset;
    sample_square(&offset);


    Vec3 pixel_u = cam->pixel_delta_u;
    double x = (i + offset.x);
    vec3_scalar_mult(&pixel_u, x);

    Vec3 pixel_v = cam->pixel_delta_v;
    double y = (j + offset.y);
    vec3_scalar_mult(&pixel_v, y);

    Vec3 pixel_sample = cam->pixel00_loc;
    vec3_vec_add(&pixel_sample, &pixel_u, &pixel_sample);
    vec3_vec_add(&pixel_sample, &pixel_v, &pixel_sample);

    Vec3 ray_origin = cam->center;
    Vec3 ray_direction;
    vec3_vec_sub(&pixel_sample, &ray_origin, &ray_direction);

    r->origin = ray_origin;
    r->direction = ray_direction;
}

//Camera
void camera_initialize(Camera* cam){
    //Inicialização default
    if(cam->width == 0.0) cam->width = 800;
    if(cam->aspect_ratio == 0.0) cam->aspect_ratio = 16.0/9.0;
    if(cam->samples_per_pixel == 0.0) cam->samples_per_pixel = 10;
    if(cam->max_depth == 0) cam->max_depth = 10;

     //Image
    double aspect_ratio = cam->aspect_ratio;
    int width = cam->width;
    int height = (int) (width / aspect_ratio);
    height = (height < 1) ? 1 : height;
    cam->height = height;
    cam->pixel_samples_scale = 1.0 / cam->samples_per_pixel;

    //Viewport & Camera
    const double focal_lenght = 1.0; //Focal lenght é a distância do centro do viewport ao centro da câmera
    const double viewport_height = 2.0;
    const double viewport_width = viewport_height * ( ((double) width) / height);
    Vec3 camera_origin = {0.0, 0.0, 0.0};

    cam->center = camera_origin;

    //Para seguir a convenção de (0,0) no topo à esquerda utilizamos vetores auxiliares para calcular o espaçamento dos pixels
    // Mais detalhamento em https://raytracing.github.io/books/RayTracingInOneWeekend.html
    Vec3 viewport_u;
    vec3_init(&viewport_u, viewport_width, 0.0, 0.0);

    Vec3 viewport_v;
    vec3_init(&viewport_v,0.0, -viewport_height, 0.0);

    //Calcula o espçamento com base nos vetores anteriores
    Vec3 pixel_delta_u = viewport_u;
    Vec3 pixel_delta_v = viewport_v;

    vec3_scalar_div(&pixel_delta_u, width);
    vec3_scalar_div(&pixel_delta_v, height);

    cam->pixel_delta_u = pixel_delta_u;
    cam->pixel_delta_v = pixel_delta_v;

    //Define a posição do pixel do topo a esquerda (nosso (0,0))
    Vec3 viewport_u_half = viewport_u;
    Vec3 viewport_v_half = viewport_v;
    Vec3 view_focal;

    vec3_init(&view_focal, 0.0, 0.0, focal_lenght);
    vec3_scalar_div(&viewport_u_half, 2.0);
    vec3_scalar_div(&viewport_v_half, 2.0);

    Vec3 viewport_upper_left;
    
    vec3_vec_sub(&camera_origin, &view_focal, &viewport_upper_left);
    vec3_vec_sub(&viewport_upper_left, &viewport_u_half, &viewport_upper_left);
    vec3_vec_sub(&viewport_upper_left, &viewport_v_half, &viewport_upper_left);

    Vec3 pixel_deltas;
    vec3_vec_add(&pixel_delta_u, &pixel_delta_v, &pixel_deltas);
    vec3_scalar_mult(&pixel_deltas, 0.5);

    Vec3 pixel00_loc;
    vec3_vec_add(&viewport_upper_left, &pixel_deltas, &pixel00_loc);
    cam->pixel00_loc = pixel00_loc;
}

//Obtem a cor dos objetos a partir da lista de colisão
Color ray_color(Ray* r, Hittable_List* world, int depth){
    Hittable hit;
    Interval world_ray;
    interval_init(&world_ray, 0.001, 1000000.0);
    Material hit_material;

    //Não há mais luz para ser coletada
    if (depth <= 0){
        Color max_d = {0.0,0.0,0.0};
        return max_d;
    }

    if(hit_list(world, r, &world_ray, &hit, &hit_material)){
        Ray scattered;
        Color attenuation;
        
        if(hit_material.scatter(hit_material.material_data, r, &(hit.point), &(hit.normal), hit.front_face, &attenuation, &scattered)){
            Color a = ray_color(&scattered, world, depth-1);
            attenuation.r *= a.r;
            attenuation.g *= a.g;
            attenuation.b *= a.b;

            return attenuation;
        }

        Color c = {0.0, 0.0, 0.0};


        return c;
    }
    
    Vec3 unit_direction = r->direction;
    vec3_normalize(&unit_direction);
    double t = 0.5 * (unit_direction.y + 1.0);

    Color start = {1.0,1.0,1.0};
    Color end = {0.5, 0.7, 1.0};

    double lerp_r = (1.0 - t) * start.r + t * end.r;
    double lerp_g = (1.0 - t) * start.g + t * end.g;
    double lerp_b = (1.0 - t) * start.b + t * end.b;

    Color c = {lerp_r, lerp_g, lerp_b };
    return c;
}

void render(Camera* cam, Hittable_List* world, const char* path){

    const char* output_path = path;
    FILE *f = fopen(output_path, "wb");

    camera_initialize(cam);

    int width = cam->width;
    int height = cam->height;

    //Especificação do PPM
    fprintf(f, "P6\n");
    fprintf(f, "%d\n", width);
    fprintf(f, "%d\n", height);
    fprintf(f, "255\n");

    time_t before = clock();
    for(int y = 0; y < height ; y++){
        printf("Progresso: %d / %d \n", y+1, height);
        for(int x = 0; x < width; x++){

            Color pixel_color = {0.0, 0.0, 0.0};
            for(int sample = 0; sample < cam->samples_per_pixel; sample++){
                Ray r;
                get_ray(&r, cam, x, y);
                Color c = ray_color(&r, world, cam->max_depth);
                pixel_color.r += c.r;
                pixel_color.g += c.g;
                pixel_color.b += c.b;

                
            }

            pixel_color.r *= cam->pixel_samples_scale;
            pixel_color.g *= cam->pixel_samples_scale;
            pixel_color.b *= cam->pixel_samples_scale;
            write_color(f, &pixel_color);

        }
    }

    time_t end = clock();

    printf("Elapsed time: %lf\n", difftime(end, before));

    fclose(f);
}