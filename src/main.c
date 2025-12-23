#include "../include/utils/common.h"
#include "../include/utils/sphere.h"
#include "../include/utils/hittables_list_sphere.h"
#include <limits.h>

//Função de intersecção de esfera
double hit_sphere_intersection( Vec3* sphere_center, double radius, Ray* r){
    Vec3 oc;
    vec3_vec_sub(sphere_center, &(r->origin), &oc);


    double a = vec3_lenght_squared(&(r->direction));
    double b = vec3_dot_prod(&(r->direction), &oc);
    double c = vec3_lenght_squared(&oc) - radius * radius;
    double discriminant = b * b -  a * c;

    if(discriminant < 0){
        discriminant = -1.0;
    } else {
        discriminant = (b - sqrt(discriminant)) /( a);
    }

    return discriminant;
}



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

int main(void) {


    //Image
    const double aspect_ratio = 16.0 / 9.0;
    int width = 800;
    int height = (int) (width / aspect_ratio);
    height = (height < 1) ? 1 : height;

    //World 
    //NOTA: Por enquanto, tudo é feito de esferas, então há somente a lista de hits para esferas
    Hittable_List world;
    init_list(&world, 10);

    //Esfera 1
    Sphere s;
    Vec3 s_center = {0, 0, -1.0};
    sphere_init(&s, s_center, 0.5);
    add_sphere(&world, s);

    //Esfera 2
    Sphere s2;
    Vec3 s2_center = {0, -100.5, -1.0};
    sphere_init(&s2, s2_center, 100);
    add_sphere(&world, s2);

    //Esfera 3
    Sphere s3;
    Vec3 s3_center = {0.75, 0, -1.5};
    sphere_init(&s3, s3_center, 0.25);
    add_sphere(&world, s3);

    //Esfera 4
    Sphere s4;
    Vec3 s4_center = {-0.25, 0, -0.25};
    sphere_init(&s4, s4_center, 0.25);
    add_sphere(&world, s4);





    
    //Viewport & Camera
    const double focal_lenght = 1.0; //Focal lenght é a distância do centro do viewport ao centro da câmera
    const double viewport_height = 2.0;
    const double viewport_width = viewport_height * ( ((double) width) / height);
    Vec3 camera_origin = {0.0, 0.0, 0.0};

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

    const char* output_path = "image.ppm";
    FILE *f = fopen(output_path, "wb");

    //Especificação do PPM
    fprintf(f, "P6\n");
    fprintf(f, "%d\n", width);
    fprintf(f, "%d\n", height);
    fprintf(f, "255\n");


    //Render
    for(int y = 0; y < height ; y++){
        printf("Progresso: %d / %d \n", y+1, height);
        for(int x = 0; x < width; x++){
            Vec3 pixel_u = pixel_delta_u;
            Vec3 pixel_v = pixel_delta_v;


            vec3_scalar_mult(&pixel_u, (double) x);
            vec3_scalar_mult(&pixel_v, (double) y);
            Vec3 deltas;
            vec3_vec_add(&pixel_u, &pixel_v, &deltas);


            Vec3 pixel_center;

            vec3_vec_add(&pixel00_loc, &deltas, &pixel_center);

            Vec3 ray_direction;
            vec3_vec_sub(&pixel_center, &camera_origin, &ray_direction);

            Ray r;
            ray_init(&r, camera_origin, ray_direction);


            Color pixel_color;
            pixel_color = ray_color(&r, &world);
            write_color(f, &pixel_color);
        }
    }

    fclose(f);
    free_list(&world);


    return 0;
}