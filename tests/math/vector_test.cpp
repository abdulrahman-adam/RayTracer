#include <gtest/gtest.h>

#include "raytracer/math/vector.hpp"

TEST(Vector, AddsTwoVectors)
{
    raytracer::Vector a(1.0, 2.0, 3.0);
    raytracer::Vector b(4.0, 5.0, 6.0);

    raytracer::Vector result = a + b;

    EXPECT_DOUBLE_EQ(result.x(), 5.0);
    EXPECT_DOUBLE_EQ(result.y(), 7.0);
    EXPECT_DOUBLE_EQ(result.z(), 9.0);
}

TEST(Vector, SubtractsTwoVectors)
{
    raytracer::Vector a(-1.0, 4.0, 0.0);
    raytracer::Vector b(-5.0, 2.0, 1.0);

    raytracer::Vector result = a - b;

    EXPECT_DOUBLE_EQ(result.x(), 4.0);
    EXPECT_DOUBLE_EQ(result.y(), 2.0);
    EXPECT_DOUBLE_EQ(result.z(), -1.0);
}

TEST(Vector, MultipliesByScalar)
{
    raytracer::Vector v(1.0, -2.0, 3.5);

    raytracer::Vector result = v * 2.0;

    EXPECT_DOUBLE_EQ(result.x(), 2.0);
    EXPECT_DOUBLE_EQ(result.y(), -4.0);
    EXPECT_DOUBLE_EQ(result.z(), 7.0);
}

TEST(Vector, MultipliesScalarByVector)
{
    raytracer::Vector v(1.0, -2.0, 3.5);

    raytracer::Vector result = 2.0 * v;

    EXPECT_DOUBLE_EQ(result.x(), 2.0);
    EXPECT_DOUBLE_EQ(result.y(), -4.0);
    EXPECT_DOUBLE_EQ(result.z(), 7.0);
}
