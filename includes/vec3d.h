#pragma once

struct Vec {
    float x, y, z;
};

Vec operator +(const Vec& v1, const Vec& v2);
Vec operator *(float a, const Vec& v);
Vec operator /(const Vec& v, float a);
Vec operator -(const Vec& v1, const Vec& v2);

void operator+=(Vec& v1, const Vec& v2);
void operator-=(Vec& v1, const Vec& v2);

//produit scalaire
float operator |(const Vec& v1, const Vec& v2);
