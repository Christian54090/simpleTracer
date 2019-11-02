#include <iostream>
#include <fstream>
#include "Vec.h"

typedef Vec3<float> Vec3f;
typedef Vec3<float> Color;

struct Ray {
    Vec3f origin, direction;
    Ray(Vec3f o, Vec3f d) : origin(o), direction(d) {}
};

void render() {
    const int W = 500;
    const int H = 500;

    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            // Send a ray through the pixel
            Ray ray(Vec3f(x,y,0), Vec3f(0,0,1));

            // Check for intersections
        }
    }
}

int main() {
    render();
    return 0;
}