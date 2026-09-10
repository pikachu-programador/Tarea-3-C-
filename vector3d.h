#ifndef UNTITLED3_VECTOR3D_H
#define UNTITLED3_VECTOR3D_H

#include <cstddef>
#include <ostream>

// Clase de prueba: cumple Addable, Subtractable, Multiplicable, Divisible y Comparable
class Vector3D {
public:
    double x, y, z;

    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    // Producto por componentes (Hadamard)
    Vector3D operator*(const Vector3D& other) const {
        return Vector3D(x * other.x, y * other.y, z * other.z);
    }

    Vector3D operator/(std::size_t n) const {
        return Vector3D(x / static_cast<double>(n), y / static_cast<double>(n), z / static_cast<double>(n));
    }

    // Compara por magnitud
    bool operator>(const Vector3D& other) const {
        double magA = x * x + y * y + z * z;
        double magB = other.x * other.x + other.y * other.y + other.z * other.z;
        return magA > magB;
    }

    bool operator==(const Vector3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

#endif //UNTITLED3_VECTOR3D_H
