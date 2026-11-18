#pragma once

#include "math/vector.hpp"

namespace raytracer {

// A ray in 3D space: a starting point (origin) and the direction it travels.
class Ray {
public:
    // Creates a ray that starts at `origin` and travels along `direction`.
    Ray(const Vector& origin, const Vector& direction);

    // Read-only access to the origin and direction.
    const Vector& origin() const;
    const Vector& direction() const;

private:
    Vector _origin;
    Vector _direction;
};

} // namespace raytracer
