#pragma once

#include "math/vector.hpp"

// A ray in 3D space: a starting point (origin) and the direction it travels.
class Ray {
public:
    // Creates a ray that starts at `origin` and travels along `direction`.
    Ray(const Vector& origin, const Vector& direction);

    // Read-only access to the origin and direction.
    const Vector& origin() const;
    const Vector& direction() const;

    // The point reached after travelling `t` times the direction from the
    // origin: origin + t * direction. With a non-unit direction, `t` is not
    // a distance.
    Vector at(double t) const;

private:
    Vector _origin;
    Vector _direction;
};
