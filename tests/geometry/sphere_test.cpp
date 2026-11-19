#include <gtest/gtest.h>

#include <memory>
#include <optional>

#include "colour/colour.hpp"
#include "geometry/hit_info.hpp"
#include "geometry/shape.hpp"
#include "geometry/sphere.hpp"
#include "light/light.hpp"
#include "material/flat_shader.hpp"
#include "ray/ray.hpp"
#include "test_helpers.hpp"

const auto red = std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0));

TEST(Sphere, StoresCenterAndRadius)
{
    Sphere sphere(Vector(1.0, 2.0, 3.0), 4.0, red);

    expectVector(sphere.center(), 1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(sphere.radius(), 4.0);
}

TEST(Sphere, StoresMaterial)
{
    const auto material = std::make_shared<FlatShader>(Colour(0.25, 0.5, 0.75));
    Sphere sphere(Vector(1.0, 2.0, 3.0), 4.0, material);

    EXPECT_EQ(&sphere.material(), material.get());

    const HitInfo anyHit{Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), material.get(), 1.0};
    const Light anyLight(Vector(0.0, 5.0, 0.0), white);
    expectColour(sphere.material().shade(anyHit, anyLight), 0.25, 0.5, 0.75);
}

// All the hit tests use a sphere of radius 1 centered 5 units along the Z-axis.

TEST(Sphere, IsHitByRayPointingAtIt)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    EXPECT_TRUE(sphere.hit(ray).has_value());
}

TEST(Sphere, HitPointIsTheNearSideOfTheSphere)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    const std::optional<HitInfo> hit = sphere.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 0.0, 0.0, 4.0);
}

TEST(Sphere, HitNormalPointsOutFromTheCenter)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    const std::optional<HitInfo> hit = sphere.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->normal, 0.0, 0.0, -1.0);
}

// A sphere of radius 2 gives a center-to-surface vector of length 2, so the
// normal is only (0, 0, -1) if it is normalised.
TEST(Sphere, HitNormalHasUnitLength)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 2.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    const std::optional<HitInfo> hit = sphere.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 0.0, 0.0, 3.0);
    expectVector(hit->normal, 0.0, 0.0, -1.0);
}

TEST(Sphere, HitCarriesTheSphereMaterial)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    const std::optional<HitInfo> hit = sphere.hit(ray);

    ASSERT_TRUE(hit.has_value());
    EXPECT_EQ(hit->material, red.get());
}

TEST(Sphere, IsMissedByRayPassingBesideIt)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(2.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    EXPECT_FALSE(sphere.hit(ray).has_value());
}

TEST(Sphere, IsMissedWhenItIsBehindTheRay)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0));

    EXPECT_FALSE(sphere.hit(ray).has_value());
}

// From the center, the near intersection is behind the ray (t = -1), so the
// hit is the far side, where the ray leaves the sphere (t = 1).
TEST(Sphere, RayStartingInsideItHitsTheFarSide)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 5.0), Vector(0.0, 0.0, 1.0));

    const std::optional<HitInfo> hit = sphere.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 0.0, 0.0, 6.0);
    expectVector(hit->normal, 0.0, 0.0, 1.0);
}

TEST(Sphere, RayTouchingItsEdgeHitsWithSidewaysNormal)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(1.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    const std::optional<HitInfo> hit = sphere.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 1.0, 0.0, 5.0);
    expectVector(hit->normal, 1.0, 0.0, 0.0);
}

// With direction (0, 0, 10) the hit is at t = 0.4, but the point is the same.
TEST(Sphere, RayWithNonUnitDirectionHitsTheSamePoint)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 10.0));

    const std::optional<HitInfo> hit = sphere.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 0.0, 0.0, 4.0);
    expectVector(hit->normal, 0.0, 0.0, -1.0);
}

// The hit point is origin + t * direction. From the origin along (0, 0, 1),
// the near side z = 4 is reached at t = 4.
TEST(Sphere, HitCarriesTheRayParameter)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    const std::optional<HitInfo> hit = sphere.hit(ray);

    ASSERT_TRUE(hit.has_value());
    EXPECT_DOUBLE_EQ(hit->t, 4.0);
}

// With direction (0, 0, 10) the same point z = 4 is reached at t = 0.4.
TEST(Sphere, HitRayParameterDependsOnTheDirectionLength)
{
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 10.0));

    const std::optional<HitInfo> hit = sphere.hit(ray);

    ASSERT_TRUE(hit.has_value());
    EXPECT_DOUBLE_EQ(hit->t, 0.4);
}

// A sphere can be used wherever a Shape is expected (Liskov substitution).
TEST(Sphere, IsHitThroughTheShapeInterface)
{
    const Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, red);
    const Shape& shape = sphere;
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    const std::optional<HitInfo> hit = shape.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 0.0, 0.0, 4.0);
    EXPECT_EQ(hit->material, red.get());
}
