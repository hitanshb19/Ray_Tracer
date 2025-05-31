#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace std;

class Vec3 {
public:
    float x, y, z;

    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const { 
        return Vec3(x + v.x, y + v.y, z + v.z); 
    }

    Vec3 operator-(const Vec3& v) const { 
        return Vec3(x - v.x, y - v.y, z - v.z); 
    }

    Vec3 operator*(float scalar) const { 
        return Vec3(x * scalar, y * scalar, z * scalar); 
    }

    Vec3 operator/(float scalar) const { 
        return Vec3(x / scalar, y / scalar, z / scalar); 
    }

    Vec3 operator-() const { 
        return Vec3(-x, -y, -z); 
    }

    Vec3 unit() const {
        float len = length();
        if (len == 0) return Vec3(0,0,0);
        return *this / len;
    }

    float length() const { 
        return sqrt(x*x + y*y + z*z); 
    }

    float dot(const Vec3& other) const { 
        return x*other.x + y*other.y + z*other.z; 
    }

    Vec3 cross(const Vec3& other) const {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    Vec3 reflect(const Vec3& normal) const {
        return *this - normal * (2 * this->dot(normal));
    }

    Vec3 refract(const Vec3& normal, float refractive_index) const {
        float cosi = fmax(-1.0f, fmin(1.0f, this->dot(normal)));
        float etai = 1, etat = refractive_index;
        Vec3 n = normal;
        if (cosi < 0) { cosi = -cosi; }
        else { swap(etai, etat); n = -normal; }
        float eta = etai / etat;
        float k = 1 - eta * eta * (1 - cosi * cosi);
        if (k < 0)
            return Vec3(0, 0, 0);
        else
            return *this * eta + n * (eta * cosi - sqrt(k));
    }

    friend ostream& operator<<(ostream& os, const Vec3& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

#endif
