#include <iostream>
#include <fstream>
#include <cmath>
#include "Vec.h"
#include "Shapes.h"

struct Sphere;

void render(Sphere &sphere) {
    const int W = 1024;
    const int H = 768;
    const int fov = M_PI/2.;

    Color white(255,255,255);
    Color red(255,0,0);

    Color black(0,0,0);

    float t0;

    std::ofstream img("out.ppm");
    img << "P3\n" << W << ' ' << H << ' ' << "255\n";
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            // Send a ray through the pixel
            double vx = (2*( (float)x + 0.5f) / (float)W - 1)*tan(fov/2.)*W / float(H);
            double vy = -(2*( (float)y + 0.5f) / (float)H - 1)*tan(fov/2.);
            const Ray ray(Vec3f(0,0,0), Vec3f(vx,vy,-1).normalize());

            // Check for intersections
            if (sphere.intersect(ray, t0)) {
                // img << (int)102 << ' ' << (int)102 << ' ' << (int)76.5 << "\n";
                img << red.x << ' ' << red.y << ' ' << red.z << "\n";
            } else {
                // img << (int)51 << ' ' << (int)178.5 << ' ' << (int)204 << "\n";
                img << black.x << ' ' << black.y << ' ' << black.z << "\n";
            }
        }
    }
}

int main() {
    Sphere sphere(Vec3f(-3,0,-16), 2);
    render(sphere);
    return 0;
}