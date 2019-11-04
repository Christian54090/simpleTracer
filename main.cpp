#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Vec.h"
#include "Shapes.h"
#include "Texture.h"
#include "Light.h"

struct Sphere;
struct Texture;
struct Light;

void clamp(Color &color) {
    color.x = color.x < 0 ? 0 : color.x > 255 ? 255 : color.x;
    color.y = color.y < 0 ? 0 : color.y > 255 ? 255 : color.y;
    color.z = color.z < 0 ? 0 : color.z > 255 ? 255 : color.z;
}

bool intersect(
        const Ray &ray,
        const std::vector<Sphere> &spheres,
        Texture &texture,
        Vec3f &point,
        Vec3f &N
) {
    float spheres_distance = 1000;
    for (auto & sphere : spheres) {
        float t0;
        if (sphere.intersect(ray, t0) && t0 < spheres_distance) {
            spheres_distance = t0;
            point = ray.origin + ray.direction * t0;
            N = (point - sphere.center).normalize();
            texture = sphere.texture;
        }
    }
    return spheres_distance < 1000;
}

Vec3f reflect(const Vec3f &I, const Vec3f &N) {
    return I - N*2.f*(I.dot(N));
}

Vec3f light_multiplier(
        const std::vector<Light> &lights,
        const std::vector<Sphere> &spheres,
        const Ray &ray,
        const Texture &texture,
        Texture &reflect_texture,
        Vec3f &point,
        Vec3f &N
) {
    float diffuse_multiplier = 0, specular_multiplier = 0;
    for (auto & light : lights) {
        Vec3f light_direction = (light.position - point).normalize();
        float light_distance = (light.position - point).length();
        Vec3f shadow_origin = (light_direction*N).length() < 0 ? point-N*1e-3 : point + N*1e-3;

        Ray shadow_ray(shadow_origin, light_direction);
        Vec3f shadow_pt, shadow_N;
        Texture tmp;
        if (intersect(shadow_ray, spheres, tmp, shadow_pt, shadow_N) &&
            (shadow_pt-shadow_origin).length() < light_distance)
            continue;

        diffuse_multiplier += light.intensity * std::max(0.f, light_direction.dot(N));
        specular_multiplier += powf(
                std::max(0.f, ray.direction.dot(reflect(light_direction,N))),
                texture.specular*light.intensity
        );
    }
    return texture.color * diffuse_multiplier * texture.albedo.x +
        Vec3f(255.,255.,255.) * specular_multiplier * texture.albedo.y +
        reflect_texture.color * texture.albedo.z;
}

Color send_ray(
        const Ray &ray,
        const std::vector<Sphere> &spheres,
        const std::vector<Light> &lights,
        size_t reflection_depth=0
) {
    Vec3f point, N;
    Texture texture;

    Color background(128,128,128);  // gray

    if (reflection_depth > 4 || !intersect(ray, spheres, texture, point, N))
        return background;

    Vec3f reflect_direction = reflect(ray.direction, N).normalize();
    Vec3f reflect_origin = reflect_direction.dot(N) < 0 ? point-N*1e-3 : point+N*1e-3;
    Ray reflect_ray(reflect_origin, reflect_direction);

    Texture reflect_texture;
    reflect_texture.color = send_ray(reflect_ray, spheres, lights, reflection_depth+1);

    return light_multiplier(lights, spheres, ray, texture, reflect_texture, point, N);
}

void render(const std::vector<Sphere> &spheres, const std::vector<Light> &lights) {
    const int W = 1024;
    const int H = 768;
    const int fov = M_PI/2.;

//    Color background(128,128,128);  // gray

    Texture texture;

    std::ofstream img("out.ppm");
    img << "P3\n" << W << ' ' << H << ' ' << "255\n";
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            // Send a ray through the pixel
            double vx = (2*( (float)x + 0.5f) / (float)W - 1)*tan(fov/2.)*W / float(H);
            double vy = -(2*( (float)y + 0.5f) / (float)H - 1)*tan(fov/2.);
            Ray ray(Vec3f(0,0,0), Vec3f(vx,vy,-1).normalize());

            texture.color = send_ray(ray, spheres, lights);

            clamp(texture.color);

            img << (int)texture.color.x << ' '
                << (int)texture.color.y << ' '
                << (int)texture.color.z << "\n";
        }
    }
}

int main() {
    Texture ivory(Color(102,102,76.5), Vec3f(0.6,0.3,0), 50.);
    Texture red_rubber(Color(76.5,25.5,25.5), Vec3f(0.9,0.1,0), 10.);
    Texture mirror(Color(255,255,255), Vec3f(0.0,10.0,0.8), 1425.);
    Texture gold(Color(255,215,0), Vec3f(0.2,10.0,0.45), 300.);

    std::vector<Sphere> spheres;
    spheres.emplace_back(Vec3f(-3,0,-16), 2, ivory);
    spheres.emplace_back(Vec3f(-1,-1.5,-12), 2, gold);
    spheres.emplace_back(Vec3f(1.5,-0.5,-18), 3, red_rubber);
    spheres.emplace_back(Vec3f(7,5,-18), 4, mirror);

    std::vector<Light> lights;
    lights.emplace_back(Vec3f(-20,20,20), 1.5);
    lights.emplace_back(Vec3f(30,50,-25), 1.8);
    lights.emplace_back(Vec3f(30,20,30), 1.7);

    render(spheres, lights);
    return 0;
}