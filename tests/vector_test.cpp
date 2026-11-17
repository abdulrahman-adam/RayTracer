#include <gtest/gtest.h>

#include "raytracer/vector.hpp"

TEST(Vector, AddsTwoVectors)
{
    raytracer::Vector a(1.0, 2.0, 3.0);
    raytracer::Vector b(4.0, 5.0, 6.0);

    raytracer::Vector result = a.add(b);

    EXPECT_DOUBLE_EQ(result.getX(), 5.0);
    EXPECT_DOUBLE_EQ(result.getY(), 7.0);
    EXPECT_DOUBLE_EQ(result.getZ(), 9.0);
}

TEST(Vector, SubtractsTwoVectors)
{
    raytracer::Vector a(-1.0, 4.0, 0.0);
    raytracer::Vector b(-5.0, 2.0, 1.0);

    raytracer::Vector result = a.subtract(b);

    EXPECT_DOUBLE_EQ(result.getX(), 4.0);
    EXPECT_DOUBLE_EQ(result.getY(), 2.0);
    EXPECT_DOUBLE_EQ(result.getZ(), -1.0);
}
