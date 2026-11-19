#include <gtest/gtest.h>

#include "ray/ray.hpp"

TEST(Ray, StoresOriginAndDirection)
{
    Vector origin(1.0, 2.0, 3.0);
    Vector direction(0.0, 0.0, 1.0);

    Ray ray(origin, direction);

    EXPECT_DOUBLE_EQ(ray.origin().x(), 1.0);
    EXPECT_DOUBLE_EQ(ray.origin().y(), 2.0);
    EXPECT_DOUBLE_EQ(ray.origin().z(), 3.0);

    EXPECT_DOUBLE_EQ(ray.direction().x(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().y(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().z(), 1.0);
}

TEST(Ray, AtZeroIsTheOrigin)
{
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(4.0, 5.0, 6.0));

    Vector point = ray.at(0.0);

    EXPECT_DOUBLE_EQ(point.x(), 1.0);
    EXPECT_DOUBLE_EQ(point.y(), 2.0);
    EXPECT_DOUBLE_EQ(point.z(), 3.0);
}

TEST(Ray, AtMovesAlongTheDirectionScaledByT)
{
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(4.0, 5.0, 6.0));

    Vector point = ray.at(0.5);

    EXPECT_DOUBLE_EQ(point.x(), 3.0);
    EXPECT_DOUBLE_EQ(point.y(), 4.5);
    EXPECT_DOUBLE_EQ(point.z(), 6.0);
}

TEST(Ray, AtNegativeTGoesBackwards)
{
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    Vector point = ray.at(-2.0);

    EXPECT_DOUBLE_EQ(point.x(), 0.0);
    EXPECT_DOUBLE_EQ(point.y(), 0.0);
    EXPECT_DOUBLE_EQ(point.z(), -2.0);
}
