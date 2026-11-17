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
    double getX() const;
    double getY() const;
    double getZ() const;

    // Returns a new vector that is this vector plus `other`.
    // Neither vector is changed.
    Vector add(const Vector& other) const;

    // Returns a new vector that is this vector minus `other`.
    // Neither vector is changed.
    Vector subtract(const Vector& other) const;

private:
    double x_;
    double y_;
    double z_;
};

} // namespace raytracer
