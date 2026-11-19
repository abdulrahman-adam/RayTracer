#pragma once

#include "colour/colour.hpp"
#include "material/material.hpp"

// A material with a single colour, the same everywhere on the surface.
class FlatShader : public Material {
public:
    // Creates a material that always shades with `colour`.
    explicit FlatShader(const Colour& colour);

    // Returns the material's colour, whatever the hit and the light.
    Colour shade(const HitInfo& hit, const Light& light) const override;

private:
    Colour _colour;
};
