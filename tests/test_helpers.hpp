#pragma once

#include <gtest/gtest.h>

#include "colour/colour.hpp"
#include "math/vector.hpp"

// Shared by the test files, so each check is written once.

inline const Colour white(1.0, 1.0, 1.0);

// Checks each component of `v` against `x`, `y` and `z`.
inline void expectVector(const Vector& v, double x, double y, double z)
{
    EXPECT_DOUBLE_EQ(v.x(), x);
    EXPECT_DOUBLE_EQ(v.y(), y);
    EXPECT_DOUBLE_EQ(v.z(), z);
}

// Checks each component of `c` against `r`, `g` and `b`.
inline void expectColour(const Colour& c, double r, double g, double b)
{
    EXPECT_DOUBLE_EQ(c.r(), r);
    EXPECT_DOUBLE_EQ(c.g(), g);
    EXPECT_DOUBLE_EQ(c.b(), b);
}
