//
// Created by csanders on 11/2/19.
//

#ifndef SIMPLETRACER_VEC_H
#define SIMPLETRACER_VEC_H

#include <cmath>

template<typename T>
struct Vec3 {
    T x,y,z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(T a, T b, T c) : x(a), y(b), z(c) {}

    Vec3<T> operator * (Vec3<T> v) { return Vec3<T>(x*v.x,y*v.y,z*v.z); }
    Vec3<T> operator * (float v) { return Vec3<T>(x*v,y*v,z*v); }
    Vec3<T> operator - (Vec3<T> v) { return Vec3<T>(x-v.x,y-v.y,z-v.z); }

    T dot(Vec3<T> a) { return x*a.x+y*a.y+z*a.z; }
    Vec3<T> cross(Vec3<T> a) { return Vec3<T>(y*a.z-z*a.y, z*a.x-x*a.z, x*a.y-y*a.x); }
    T length() { return std::sqrt(x*x+y*y+z*z); }
    Vec3<T> normalize() { *this = (*this)*(1/length()); return *this; }
};

typedef Vec3<float> Vec3f;
typedef Vec3<float> Color;

struct Ray {
    Vec3f origin, direction;
    Ray(Vec3f o, Vec3f d) : origin(o), direction(d) {}
};

#endif //SIMPLETRACER_VEC_H
