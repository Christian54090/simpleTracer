//
// Created by csanders on 11/3/19.
//

#ifndef SIMPLETRACER_LIGHT_H
#define SIMPLETRACER_LIGHT_H

#include "Vec.h"

struct Light {
    Vec3f position;
    float intensity;

    Light(const Vec3f p, const float i) : position(p), intensity(i) {}
};


#endif //SIMPLETRACER_LIGHT_H
