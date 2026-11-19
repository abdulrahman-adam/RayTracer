#include <gtest/gtest.h>

#include <memory>
#include <optional>

#include "colour/colour.hpp"
#include "geometry/hit_info.hpp"
#include "geometry/plane.hpp"
#include "geometry/shape.hpp"
#include "material/flat_shader.hpp"
#include "ray/ray.hpp"
#include "test_helpers.hpp"

static const auto grey = std::make_shared<FlatShader>(Colour(0.5, 0.5, 0.5));

TEST(Plane, StoresPointNormalAndMaterial)
{
    Plane plane(Vector(1.0, 2.0, 3.0), Vector(0.0, 1.0, 0.0), grey);

    expectVector(plane.point(), 1.0, 2.0, 3.0);
    expectVector(plane.normal(), 0.0, 1.0, 0.0);
    EXPECT_EQ(&plane.material(), grey.get());
}

// The normal is given as (0, 5, 0) but stored with length 1.
TEST(Plane, NormalIsNormalised)
{
    Plane plane(Vector(0.0, 0.0, 0.0), Vector(0.0, 5.0, 0.0), grey);

    expectVector(plane.normal(), 0.0, 1.0, 0.0);
}

// Most hit tests use a floor: the plane y = -1, facing up.

TEST(Plane, RayPointingDownHitsTheFloorBelowIt)
{
    Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), grey);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, -1.0, 0.0));

    const std::optional<HitInfo> hit = floor.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 0.0, -1.0, 0.0);
    expectVector(hit->normal, 0.0, 1.0, 0.0);
    EXPECT_DOUBLE_EQ(hit->t, 1.0);
}

// Along (0, -1, 1) the ray drops 1 unit for every unit forward, so it
// reaches y = -1 at z = 1, at t = 1.
TEST(Plane, RayAtAnAngleHitsTheFloorAhead)
{
    Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), grey);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, -1.0, 1.0));

    const std::optional<HitInfo> hit = floor.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 0.0, -1.0, 1.0);
    EXPECT_DOUBLE_EQ(hit->t, 1.0);
}

// The point given to the constructor is just one point on the plane: any
// other point at the same height describes the same floor.
TEST(Plane, HitDoesNotDependOnWhichPointDefinesThePlane)
{
    Plane floor(Vector(7.0, -1.0, -3.0), Vector(0.0, 1.0, 0.0), grey);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, -1.0, 1.0));

    const std::optional<HitInfo> hit = floor.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 0.0, -1.0, 1.0);
}

// A wall: the plane z = 5, facing the camera. Along (1, 0, 1) the ray reaches
// it at x = 5, at t = 5.
TEST(Plane, RayHitsAWallInFrontOfIt)
{
    Plane wall(Vector(0.0, 0.0, 5.0), Vector(0.0, 0.0, -1.0), grey);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(1.0, 0.0, 1.0));

    const std::optional<HitInfo> hit = wall.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 5.0, 0.0, 5.0);
    expectVector(hit->normal, 0.0, 0.0, -1.0);
    EXPECT_DOUBLE_EQ(hit->t, 5.0);
}

TEST(Plane, HitCarriesThePlaneMaterial)
{
    Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), grey);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, -1.0, 0.0));

    const std::optional<HitInfo> hit = floor.hit(ray);

    ASSERT_TRUE(hit.has_value());
    EXPECT_EQ(hit->material, grey.get());
}

TEST(Plane, IsMissedByRayParallelToIt)
{
    Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), grey);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    EXPECT_FALSE(floor.hit(ray).has_value());
}

TEST(Plane, IsMissedWhenItIsBehindTheRay)
{
    Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), grey);
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0));

    EXPECT_FALSE(floor.hit(ray).has_value());
}

// A plane can be used wherever a Shape is expected (Liskov substitution).
TEST(Plane, IsHitThroughTheShapeInterface)
{
    const Plane floor(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), grey);
    const Shape& shape = floor;
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, -1.0, 0.0));

    const std::optional<HitInfo> hit = shape.hit(ray);

    ASSERT_TRUE(hit.has_value());
    expectVector(hit->point, 0.0, -1.0, 0.0);
    EXPECT_EQ(hit->material, grey.get());
}
