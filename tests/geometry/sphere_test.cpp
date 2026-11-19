#include <gtest/gtest.h>

#include <memory>
#include <optional>

#include "colour/colour.hpp"
#include "geometry/hit_info.hpp"
#include "geometry/sphere.hpp"
#include "light/light.hpp"
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

    const HitInfo anyHit{Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), material.get()};
    const Light anyLight(Vector(0.0, 5.0, 0.0), Colour(1.0, 1.0, 1.0));
    const Colour colour = sphere.material().shade(anyHit, anyLight);
    EXPECT_DOUBLE_EQ(colour.r(), 0.25);
    EXPECT_DOUBLE_EQ(colour.g(), 0.5);
    EXPECT_DOUBLE_EQ(colour.b(), 0.75);
}

// All the hit tests use a sphere of radius 1 centered 5 units along the Z-axis.

static void expectVector(const Vector& v, double x, double y, double z)
{
    EXPECT_DOUBLE_EQ(v.x(), x);
    EXPECT_DOUBLE_EQ(v.y(), y);
    EXPECT_DOUBLE_EQ(v.z(), z);
}

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
