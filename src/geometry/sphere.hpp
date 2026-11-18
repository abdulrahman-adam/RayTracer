#pragma once

#include "geometry/ray.hpp"
#include "math/vector.hpp"

namespace raytracer {

// A sphere in 3D space, given by its center point and its radius.
class Sphere {
public:
    // Creates a sphere centered at `center` with the given `radius`.
    Sphere(const Vector& center, double radius);

    // Read-only access to the center and radius.
    const Vector& center() const;
    double radius() const;

    // Est-ce ce rayon me touch
    bool hit(const Ray& ray) const;

private:
    Vector _center;
    double _radius;
};

} // namespace raytracer
