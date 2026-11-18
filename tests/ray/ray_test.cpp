#include <gtest/gtest.h>

#include "ray/ray.hpp"

TEST(Ray, StoresOriginAndDirection)
{
    raytracer::Vector origin(1.0, 2.0, 3.0);
    raytracer::Vector direction(0.0, 0.0, 1.0);

    raytracer::Ray ray(origin, direction);

    EXPECT_DOUBLE_EQ(ray.origin().x(), 1.0);
    EXPECT_DOUBLE_EQ(ray.origin().y(), 2.0);
    EXPECT_DOUBLE_EQ(ray.origin().z(), 3.0);

    EXPECT_DOUBLE_EQ(ray.direction().x(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().y(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().z(), 1.0);
}
