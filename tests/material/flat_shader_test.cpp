#include <gtest/gtest.h>

#include "colour/colour.hpp"
#include "material/flat_shader.hpp"

TEST(FlatShader, ShadesWithItsColour)
{
    FlatShader shader(Colour(0.25, 0.5, 0.75));

    const Colour colour = shader.shade();
    EXPECT_DOUBLE_EQ(colour.r(), 0.25);
    EXPECT_DOUBLE_EQ(colour.g(), 0.5);
    EXPECT_DOUBLE_EQ(colour.b(), 0.75);
}

TEST(FlatShader, ShadesThroughTheMaterialInterface)
{
    FlatShader shader(Colour(1.0, 0.0, 0.0));
    const Material& material = shader;

    const Colour colour = material.shade();
    EXPECT_DOUBLE_EQ(colour.r(), 1.0);
    EXPECT_DOUBLE_EQ(colour.g(), 0.0);
    EXPECT_DOUBLE_EQ(colour.b(), 0.0);
}
