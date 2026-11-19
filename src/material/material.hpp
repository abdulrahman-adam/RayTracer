#pragma once

#include "colour/colour.hpp"
#include "light/light.hpp"

// Declared here rather than included: hit_info.hpp includes this header, so
// including it back would be circular. shade() only takes it by reference.
struct HitInfo;

// Decides the colour of a surface where a ray hits it.
// Each shading model is its own subclass (see FlatShader and LambertShader).
class Material {
public:
    virtual ~Material() = default;

    // The colour of the surface at the hit point described by `hit`, lit by
    // `light`. Shading models are free to ignore either argument.
    virtual Colour shade(const HitInfo& hit, const Light& light) const = 0;
};
