
#include "../../include/utils/hittable.h"
#include "../../include/utils/color.h"
#include "../../include/utils/interval.h"
#include "../../include/utils/hittables_list_sphere.h"
#include <stdio.h>

typedef struct camera {
    int width;
    int height;
    double aspect_ratio;
    int image_height;
    Vec3 center;
    Vec3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
} Camera;

//Camera
void camera_initialize(Camera* cam){
    //Inicialização default
    if(cam->width == 0.0) cam->width = 800;
    if(cam->aspect_ratio == 0.0) cam->aspect_ratio = 16.0/9.0;

     //Image
    double aspect_ratio = cam->aspect_ratio;
    int width = cam->width;
    int height = (int) (width / aspect_ratio);
    height = (height < 1) ? 1 : height;
    cam->height = height;

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
Color ray_color(Ray* r, Hittable_List* world){
    Hittable hit;
    Interval world_ray;
    interval_init(&world_ray, 0.0, 1000000.0);

    if(hit_list(world, r, &world_ray, &hit)){
        Vec3 d = {1.0,1.0,1.0};
        Vec3 e = hit.normal;

        vec3_vec_add(&e, &d, &e);
        vec3_scalar_mult(&e, 0.5);

        Color o = {e.x, e.y, e.z};
        return o;
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


    for(int y = 0; y < height ; y++){
        printf("Progresso: %d / %d \n", y+1, height);
        for(int x = 0; x < width; x++){
            Vec3 pixel_u = cam->pixel_delta_u;
            Vec3 pixel_v = cam->pixel_delta_v;


            vec3_scalar_mult(&pixel_u, (double) x);
            vec3_scalar_mult(&pixel_v, (double) y);
            Vec3 deltas;
            vec3_vec_add(&pixel_u, &pixel_v, &deltas);


            Vec3 pixel_center;

            vec3_vec_add(&(cam->pixel00_loc), &deltas, &pixel_center);

            Vec3 ray_direction;
            vec3_vec_sub(&pixel_center, &(cam->center), &ray_direction);

            Ray r;
            ray_init(&r, cam->center, ray_direction);

            Color pixel_color;
            pixel_color = ray_color(&r, world);
            write_color(f, &pixel_color);
        }
    }

    fclose(f);
}