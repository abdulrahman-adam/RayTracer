#pragma once

#include "colour/colour.hpp"

// Decides the colour of a surface where a ray hits it.
// Each shading model is its own subclass (see FlatShader).
class Material {
public:
    virtual ~Material() = default;

    // The colour of the surface at the hit point.
    virtual Colour shade() const = 0;
};
