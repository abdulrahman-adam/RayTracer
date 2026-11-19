#include <gtest/gtest.h>

#include <memory>

#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "material/flat_shader.hpp"
#include "ray/ray.hpp"

const auto red = std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0));

TEST(Sphere, StoresCenterAndRadius)
{
    Sphere sphere(Vector(1.0, 2.0, 3.0), 4.0, red);

    EXPECT_DOUBLE_EQ(sphere.center().x(), 1.0);
    EXPECT_DOUBLE_EQ(sphere.center().y(), 2.0);
    EXPECT_DOUBLE_EQ(sphere.center().z(), 3.0);
    EXPECT_DOUBLE_EQ(sphere.radius(), 4.0);
}

TEST(Sphere, StoresMaterial)
{
    const auto material = std::make_shared<FlatShader>(Colour(0.25, 0.5, 0.75));
    Sphere sphere(Vector(1.0, 2.0, 3.0), 4.0, material);

    EXPECT_EQ(&sphere.material(), material.get());

    const Colour colour = sphere.material().shade();
    EXPECT_DOUBLE_EQ(colour.r(), 0.25);
    EXPECT_DOUBLE_EQ(colour.g(), 0.5);
    EXPECT_DOUBLE_EQ(colour.b(), 0.75);
}

// All the hit tests use a sphere of radius 1 centered 5 units along the Z-axis.

TEST(Sphere, IsHitByRayPointingAtIt)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    EXPECT_TRUE(sphere.hit(ray));
}

TEST(Sphere, IsMissedByRayPassingBesideIt)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(2.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    EXPECT_FALSE(sphere.hit(ray));
}

TEST(Sphere, IsMissedWhenItIsBehindTheRay)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0));

    EXPECT_FALSE(sphere.hit(ray));
}

TEST(Sphere, IsHitByRayStartingInsideIt)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 5.0), Vector(0.0, 0.0, 1.0));

    EXPECT_TRUE(sphere.hit(ray));
}

TEST(Sphere, IsHitByRayTouchingItsEdge)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(1.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    EXPECT_TRUE(sphere.hit(ray));
}

TEST(Sphere, IsHitByRayWithNonUnitDirection)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 10.0));

    EXPECT_TRUE(sphere.hit(ray));
}
