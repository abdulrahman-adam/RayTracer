#pragma once

#include "colour/colour.hpp"
#include "math/vector.hpp"
#include "ray/ray.hpp"

namespace raytracer {

// A sphere in 3D space, given by its center point, its radius and its colour.
class Sphere {
public:
    // Creates a sphere centered at `center` with the given `radius` and `colour`.
    Sphere(const Vector& center, double radius, const Colour& colour);

    // Read-only access to the center, radius and colour.
    const Vector& center() const;
    double radius() const;
    const Colour& colour() const;

    // Est-ce ce rayon me touch
    bool hit(const Ray& ray) const;

private:
    Vector _center;
    double _radius;
    Colour _colour;
};

} // namespace raytracer
