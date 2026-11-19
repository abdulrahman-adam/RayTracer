#include <gtest/gtest.h>

#include "colour/colour.hpp"

TEST(Colour, StoresRedGreenAndBlue)
{
    Colour colour(0.25, 0.5, 0.75);

    EXPECT_DOUBLE_EQ(colour.r(), 0.25);
    EXPECT_DOUBLE_EQ(colour.g(), 0.5);
    EXPECT_DOUBLE_EQ(colour.b(), 0.75);
}
