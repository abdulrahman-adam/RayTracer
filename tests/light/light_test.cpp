#include <gtest/gtest.h>

#include "colour/colour.hpp"
#include "light/light.hpp"
#include "math/vector.hpp"

TEST(Light, StoresPosition)
{
    Light light(Vector(1.0, 2.0, 3.0), Colour(1.0, 1.0, 1.0));

    EXPECT_DOUBLE_EQ(light.position().x(), 1.0);
    EXPECT_DOUBLE_EQ(light.position().y(), 2.0);
    EXPECT_DOUBLE_EQ(light.position().z(), 3.0);
}

TEST(Light, StoresColour)
{
    Light light(Vector(0.0, 0.0, 0.0), Colour(0.25, 0.5, 0.75));

    EXPECT_DOUBLE_EQ(light.colour().r(), 0.25);
    EXPECT_DOUBLE_EQ(light.colour().g(), 0.5);
    EXPECT_DOUBLE_EQ(light.colour().b(), 0.75);
}
