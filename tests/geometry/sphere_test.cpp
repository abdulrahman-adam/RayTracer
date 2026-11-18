#include <gtest/gtest.h>

#include "geometry/sphere.hpp"
#include "ray/ray.hpp"

using raytracer::Ray;
using raytracer::Sphere;
using raytracer::Vector;

TEST(Sphere, StoresCenterAndRadius)
{
    Sphere sphere(Vector(1.0, 2.0, 3.0), 4.0);

    EXPECT_DOUBLE_EQ(sphere.center().x(), 1.0);
    EXPECT_DOUBLE_EQ(sphere.center().y(), 2.0);
    EXPECT_DOUBLE_EQ(sphere.center().z(), 3.0);
    EXPECT_DOUBLE_EQ(sphere.radius(), 4.0);
}

// All the hit tests use a sphere of radius 1 centered 5 units along the Z-axis.

TEST(Sphere, IsHitByRayPointingAtIt)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    EXPECT_TRUE(sphere.hit(ray));
}

TEST(Sphere, IsMissedByRayPassingBesideIt)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0);
    Ray ray(Vector(2.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    EXPECT_FALSE(sphere.hit(ray));
}

TEST(Sphere, IsMissedWhenItIsBehindTheRay)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0));

    EXPECT_FALSE(sphere.hit(ray));
}

TEST(Sphere, IsHitByRayStartingInsideIt)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0);
    Ray ray(Vector(0.0, 0.0, 5.0), Vector(0.0, 0.0, 1.0));

    EXPECT_TRUE(sphere.hit(ray));
}

TEST(Sphere, IsHitByRayTouchingItsEdge)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0);
    Ray ray(Vector(1.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    EXPECT_TRUE(sphere.hit(ray));
}

TEST(Sphere, IsHitByRayWithNonUnitDirection)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 10.0));

    EXPECT_TRUE(sphere.hit(ray));
}
