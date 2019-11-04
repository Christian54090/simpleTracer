//
// Created by csanders on 11/2/19.
//

#ifndef SIMPLETRACER_SHAPES_H
#define SIMPLETRACER_SHAPES_H

#include "Vec.h"
#include "Texture.h"
#include <iostream>

struct Sphere {
    Vec3f center;
    float radius;
    Texture texture;

    Sphere(Vec3f c, float r, Texture t) : center(c), radius(r), texture(t) {}

    bool intersect(const Ray &ray, float &t0) const {
        Vec3f L = center - ray.origin;      // center at origin

        float tca = L.dot(ray.direction);
        if (tca < 0) return false;

        float d2 = L.dot(L) - tca*tca;
        if (d2 > radius*radius) return false;

        float thc = std::sqrt(radius*radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;

        if (t0 < 0) t0 = t1;
        return t0 >= 0;
    }
};

struct Plane {
    Vec3f start;
    float width;
    float depth;
    Texture texture;

    Plane(Vec3f s, float w, float d, Texture t) : start(s), width(w), depth(d), texture(t) {}

    bool intersect(const Ray &ray, float &d) const {
        if (fabs(ray.direction.y) < 1e-3) return false;

        d = -(ray.origin.y + -(start.y)) / ray.direction.y;

        float end_x = start.x + width;
        float end_z = start.z + depth;
        Vec3f pt = ray.origin + ray.direction * d;

        return d > 0 && pt.x > start.x && pt.x < end_x && pt.z > start.z && pt.z < end_z;
    }
};

#endif //SIMPLETRACER_SHAPES_H
