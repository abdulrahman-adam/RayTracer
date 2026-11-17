#pragma once

namespace raytracer {

// A vector in 3D space with an x, y and z component.
class Vector {
public:
    // Creates the zero vector (0, 0, 0).
    Vector();

    // Creates a vector with the given components.
    Vector(double x, double y, double z);

    // Read-only access to the components.
    double x() const;
    double y() const;
    double z() const;

    // Returns a new vector that is this vector plus `other`, so you can
    // write `a + b`. Neither vector is changed.
    Vector operator+(const Vector& other) const;

    // Returns a new vector that is this vector minus `other`, so you can
    // write `a - b`. Neither vector is changed.
    Vector operator-(const Vector& other) const;

    // Returns a new vector with each component multiplied by `scalar`, so
    // you can write `v * 2.0`. The vector is not changed.
    Vector operator*(double scalar) const;

private:
    double _x;
    double _y;
    double _z;
};

// Returns a new vector with each component of `v` multiplied by `scalar`, so
// you can write `2.0 * v`. It is a free function, not a member, because the
// left-hand side is a number, not a Vector.
Vector operator*(double scalar, const Vector& v);

} // namespace raytracer
