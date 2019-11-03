//
// Created by csanders on 11/3/19.
//

#ifndef SIMPLETRACER_TEXTURE_H
#define SIMPLETRACER_TEXTURE_H

#include "Vec.h"

struct Texture {
    Color color;
    Vec3f albedo;
    float specular;

    Texture(const Color &c, const Vec3f a, const float s) : color(c), albedo(a), specular(s) {}
    Texture() : color(), albedo(), specular() {}
};


#endif //SIMPLETRACER_TEXTURE_H
