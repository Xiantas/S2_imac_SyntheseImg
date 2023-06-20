#include "vec3d.h"

#include <cmath>

float Vec::norm() {
    return sqrt(*this|*this);
}

Vec operator+(const Vec& v1, const Vec& v2) {
    return Vec{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
} 

Vec operator-(const Vec& v1, const Vec& v2) {
    return Vec{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vec operator*(float a, const Vec& v) {
    return Vec{a*v.x, a*v.y, a*v.z};
}

Vec operator/(const Vec& v, float a) {
    return Vec{v.x/a, v.y/a, v.z/a};
}

void operator+=(Vec& v1, const Vec& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
}

void operator-=(Vec& v1, const Vec& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
}

float operator|(const Vec& v1, const Vec& v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
