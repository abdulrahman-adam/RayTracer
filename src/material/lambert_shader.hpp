#pragma once

#include "colour/colour.hpp"
#include "material/material.hpp"

// A matte (diffuse) material, shaded with Lambert's cosine law: a surface is
// brightest where it faces the light and fades to black as it turns away.
class LambertShader : public Material {
public:
    // Creates a matte material with the given surface `colour`.
    explicit LambertShader(const Colour& colour);

    // The surface colour times the light colour, scaled by the dot product of
    // the surface normal and the direction from the hit point to the light.
    // Where the surface faces away from the light (a negative dot product),
    // the result is black.
    Colour shade(const HitInfo& hit, const Light& light) const override;

private:
    Colour _colour;
};
