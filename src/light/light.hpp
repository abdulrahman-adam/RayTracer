#pragma once

#include "colour/colour.hpp"
#include "math/vector.hpp"

// A point light: it sits at a single point in space and shines the same
// colour equally in every direction.
class Light {
public:
    // Creates a light at `position` that shines with `colour`.
    Light(const Vector& position, const Colour& colour);

    // Read-only access to the position and colour.
    const Vector& position() const;
    const Colour& colour() const;

private:
    Vector _position;
    Colour _colour;
};
