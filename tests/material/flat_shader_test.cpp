#include <gtest/gtest.h>

#include "colour/colour.hpp"
#include "geometry/hit_info.hpp"
#include "light/light.hpp"
#include "material/flat_shader.hpp"

// A flat shader ignores the hit and the light, so any will do.
static const HitInfo anyHit{Vector(0.0, 0.0, 4.0), Vector(0.0, 0.0, -1.0), nullptr, 4.0};
static const Light anyLight(Vector(0.0, 0.0, 0.0), Colour(1.0, 1.0, 1.0));

TEST(FlatShader, ShadesWithItsColour)
{
    FlatShader shader(Colour(0.25, 0.5, 0.75));

    const Colour colour = shader.shade(anyHit, anyLight);
    EXPECT_DOUBLE_EQ(colour.r(), 0.25);
    EXPECT_DOUBLE_EQ(colour.g(), 0.5);
    EXPECT_DOUBLE_EQ(colour.b(), 0.75);
}

TEST(FlatShader, ShadesThroughTheMaterialInterface)
{
    FlatShader shader(Colour(1.0, 0.0, 0.0));
    const Material& material = shader;

    const Colour colour = material.shade(anyHit, anyLight);
    EXPECT_DOUBLE_EQ(colour.r(), 1.0);
    EXPECT_DOUBLE_EQ(colour.g(), 0.0);
    EXPECT_DOUBLE_EQ(colour.b(), 0.0);
}

// The surface faces away from this light, yet a flat shader still gives its colour.
TEST(FlatShader, IgnoresTheLight)
{
    FlatShader shader(Colour(0.25, 0.5, 0.75));
    const Light behind(Vector(0.0, 0.0, 10.0), Colour(0.0, 0.0, 0.0));

    const Colour colour = shader.shade(anyHit, behind);
    EXPECT_DOUBLE_EQ(colour.r(), 0.25);
    EXPECT_DOUBLE_EQ(colour.g(), 0.5);
    EXPECT_DOUBLE_EQ(colour.b(), 0.75);
}
