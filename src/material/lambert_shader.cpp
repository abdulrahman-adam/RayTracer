#include "material/lambert_shader.hpp"

#include <algorithm>

#include "geometry/hit_info.hpp"

LambertShader::LambertShader(const Colour& colour)
    : _colour(colour)
{
}

Colour LambertShader::shade(const HitInfo& hit, const Light& light) const
{
    const Vector toLight = (light.position() - hit.point).normalised();

    // cos of the angle between the normal and the light; both have length 1.
    // Surfaces facing away from the light get no light at all.
    const double intensity = std::max(0.0, hit.normal.dot(toLight));

    const Colour& lightColour = light.colour();
    return Colour(_colour.r() * lightColour.r() * intensity,
                  _colour.g() * lightColour.g() * intensity,
                  _colour.b() * lightColour.b() * intensity);
}
