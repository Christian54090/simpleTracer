//
// Created by csanders on 11/2/19.
//

#ifndef SIMPLETRACER_VEC_H
#define SIMPLETRACER_VEC_H

template<typename T>
struct Vec3 {
    T x,y,z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(T a, T b, T c) : x(a), y(b), z(c) {}

    T dot(Vec3<T> a) { return x*a.x+y*a.y+z*a.z; }
    Vec3<T> cross(Vec3<T> a) { return Vec3<T>(y*a.z-z*a.y, z*a.x-x*a.z, x*a.y-y*a.x); }
};

#endif //SIMPLETRACER_VEC_H
