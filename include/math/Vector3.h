#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

class Vector3 {
public:
    double x, y, z;
    
    Vector3() : x(0), y(0), z(0) {}
    Vector3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}


    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(double scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator/(double scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    Vector3& operator+=(const Vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    double dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    double magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    double magnitudeSquared() const {
        return x * x + y * y + z * z;
    }

    Vector3 normalized() const {
        double mag = magnitude();
        if (mag > 0.0001) {  // Avoid division by zero
            return (*this) / mag;
        }
        return Vector3(0, 0, 0);
    }

    // Useful predefined vectors
    static Vector3 Zero()    { return Vector3(0, 0, 0); }
    static Vector3 Up()      { return Vector3(0, 0, 1); }  // Z is up (aerospace standard)
    static Vector3 Forward() { return Vector3(1, 0, 0); }  // X is forward
    static Vector3 Right()   { return Vector3(0, 1, 0); }  // Y is right

    // For easy printing: std::cout << velocity
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

#endif