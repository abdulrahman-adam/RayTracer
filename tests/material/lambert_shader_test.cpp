#include <gtest/gtest.h>

#include <cmath>

#include "colour/colour.hpp"
#include "geometry/hit_info.hpp"
#include "light/light.hpp"
#include "material/lambert_shader.hpp"
#include "test_helpers.hpp"

// All the tests shade the point (0, 0, 0) on a surface facing up, (0, 1, 0).
static const HitInfo hit{Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), nullptr, 1.0};

// Light straight above: normal and light direction are the same, dot = 1.
TEST(LambertShader, LightStraightAboveGivesFullColour)
{
    LambertShader shader(Colour(0.25, 0.5, 0.75));
    const Light light(Vector(0.0, 5.0, 0.0), white);

    expectColour(shader.shade(hit, light), 0.25, 0.5, 0.75);
}

// The distance to the light does not matter, only its direction.
TEST(LambertShader, DistanceToTheLightDoesNotMatter)
{
    LambertShader shader(Colour(0.25, 0.5, 0.75));
    const Light light(Vector(0.0, 1000.0, 0.0), white);

    expectColour(shader.shade(hit, light), 0.25, 0.5, 0.75);
}

// Light at 60 degrees from the normal: cos(60) = 0.5, so half the colour.
TEST(LambertShader, LightAtAnAngleDimsTheColourByTheCosine)
{
    LambertShader shader(Colour(1.0, 0.5, 0.0));
    const Light light(Vector(std::sqrt(3.0), 1.0, 0.0), white);

    const Colour colour = shader.shade(hit, light);
    EXPECT_NEAR(colour.r(), 0.5, 1e-12);
    EXPECT_NEAR(colour.g(), 0.25, 1e-12);
    EXPECT_NEAR(colour.b(), 0.0, 1e-12);
}

// Light level with the surface: dot = 0, so black.
TEST(LambertShader, GrazingLightGivesBlack)
{
    LambertShader shader(Colour(1.0, 1.0, 1.0));
    const Light light(Vector(5.0, 0.0, 0.0), white);

    expectColour(shader.shade(hit, light), 0.0, 0.0, 0.0);
}

// Light below the surface: the dot product is negative, but the colour is
// clamped to black rather than going negative.
TEST(LambertShader, LightBehindTheSurfaceGivesBlack)
{
    LambertShader shader(Colour(1.0, 1.0, 1.0));
    const Light light(Vector(0.0, -5.0, 0.0), white);

    expectColour(shader.shade(hit, light), 0.0, 0.0, 0.0);
}

// The light's colour filters the surface colour, component by component.
TEST(LambertShader, LightColourTintsTheSurface)
{
    LambertShader shader(Colour(1.0, 0.5, 1.0));
    const Light light(Vector(0.0, 5.0, 0.0), Colour(0.5, 1.0, 0.0));

    expectColour(shader.shade(hit, light), 0.5, 0.5, 0.0);
}

TEST(LambertShader, ShadesThroughTheMaterialInterface)
{
    LambertShader shader(Colour(0.25, 0.5, 0.75));
    const Material& material = shader;
    const Light light(Vector(0.0, 5.0, 0.0), white);

    expectColour(material.shade(hit, light), 0.25, 0.5, 0.75);
}
