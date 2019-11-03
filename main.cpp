#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include "Vec.h"
#include "Shapes.h"

struct Sphere;

bool check_intersect(const Ray ray, std::vector<Sphere> &spheres) {
    float spheres_distance = std::numeric_limits<float>::max();
    for (auto & sphere : spheres) {
        float t0;
        if (sphere.intersect(ray, t0) && t0 < spheres_distance) {
            spheres_distance = t0;
        }
    }
    return spheres_distance < 1000;
}

void render(std::vector<Sphere> &spheres) {
    const int W = 1024;
    const int H = 768;
    const int fov = M_PI/2.;

    Color white(255,255,255);
    Color red(255,0,0);
    Color black(0,0,0);

    Color color;

    std::ofstream img("out.ppm");
    img << "P3\n" << W << ' ' << H << ' ' << "255\n";
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            // Send a ray through the pixel
            double vx = (2*( (float)x + 0.5f) / (float)W - 1)*tan(fov/2.)*W / float(H);
            double vy = -(2*( (float)y + 0.5f) / (float)H - 1)*tan(fov/2.);
            const Ray ray(Vec3f(0,0,0), Vec3f(vx,vy,-1).normalize());

            color = black;

            // Check for intersections
            if (check_intersect(ray, spheres))
                color = red;
            img << color.x << ' ' << color.y << ' ' << color.z << "\n";
        }
    }
}

int main() {
    std::vector<Sphere> spheres;
    spheres.emplace_back(Vec3f(-3,0,-16), 2);
    spheres.emplace_back(Vec3f(-1,-1.5,-12), 2);
    spheres.emplace_back(Vec3f(1.5,-0.5,-18), 3);
    spheres.emplace_back(Vec3f(7,5,-18), 4);

    render(spheres);
    return 0;
}