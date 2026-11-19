#include <gtest/gtest.h>

#include <memory>
#include <optional>

#include "colour/colour.hpp"
#include "geometry/hit_info.hpp"
#include "geometry/plane.hpp"
#include "geometry/shape.hpp"
#include "geometry/sphere.hpp"
#include "light/light.hpp"
#include "material/flat_shader.hpp"
#include "ray/ray.hpp"
#include "scene/scene.hpp"

static const auto red = std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0));
static const auto blue = std::make_shared<FlatShader>(Colour(0.0, 0.0, 1.0));
static const Light whiteLight(Vector(0.0, 10.0, 0.0), Colour(1.0, 1.0, 1.0));

// All the nearestHit tests shoot this ray: from the origin along +Z.
static const Ray forward(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

TEST(Scene, StoresTheLight)
{
    const Scene scene(Light(Vector(1.0, 2.0, 3.0), Colour(0.25, 0.5, 0.75)));

    EXPECT_DOUBLE_EQ(scene.light().position().x(), 1.0);
    EXPECT_DOUBLE_EQ(scene.light().position().y(), 2.0);
    EXPECT_DOUBLE_EQ(scene.light().position().z(), 3.0);
    EXPECT_DOUBLE_EQ(scene.light().colour().r(), 0.25);
    EXPECT_DOUBLE_EQ(scene.light().colour().g(), 0.5);
    EXPECT_DOUBLE_EQ(scene.light().colour().b(), 0.75);
}

TEST(Scene, EmptySceneIsNeverHit)
{
    const Scene scene(whiteLight);

    EXPECT_FALSE(scene.nearestHit(forward).has_value());
}

TEST(Scene, NearestHitFindsTheOnlyShape)
{
    Scene scene(whiteLight);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, red));

    const std::optional<HitInfo> hit = scene.nearestHit(forward);

    ASSERT_TRUE(hit.has_value());
    EXPECT_DOUBLE_EQ(hit->point.z(), 4.0);
    EXPECT_EQ(hit->material, red.get());
}

// Two spheres in a row: the ray hits both, and the nearer one wins.
// The far one is added first, so the order of add() does not decide it.
TEST(Scene, NearestHitIsTheClosestOfSeveralShapes)
{
    Scene scene(whiteLight);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 10.0), 1.0, blue));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, red));

    const std::optional<HitInfo> hit = scene.nearestHit(forward);

    ASSERT_TRUE(hit.has_value());
    EXPECT_DOUBLE_EQ(hit->point.z(), 4.0);
    EXPECT_DOUBLE_EQ(hit->t, 4.0);
    EXPECT_EQ(hit->material, red.get());
}

// Same spheres, added the other way round: still the nearer one.
TEST(Scene, NearestHitDoesNotDependOnTheOrderShapesWereAdded)
{
    Scene scene(whiteLight);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, red));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 10.0), 1.0, blue));

    const std::optional<HitInfo> hit = scene.nearestHit(forward);

    ASSERT_TRUE(hit.has_value());
    EXPECT_EQ(hit->material, red.get());
}

TEST(Scene, NearestHitSkipsShapesTheRayMisses)
{
    Scene scene(whiteLight);
    scene.add(std::make_unique<Sphere>(Vector(5.0, 0.0, 3.0), 1.0, red));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 10.0), 1.0, blue));

    const std::optional<HitInfo> hit = scene.nearestHit(forward);

    ASSERT_TRUE(hit.has_value());
    EXPECT_EQ(hit->material, blue.get());
}

TEST(Scene, NearestHitSkipsShapesBehindTheRay)
{
    Scene scene(whiteLight);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, -5.0), 1.0, red));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 10.0), 1.0, blue));

    const std::optional<HitInfo> hit = scene.nearestHit(forward);

    ASSERT_TRUE(hit.has_value());
    EXPECT_EQ(hit->material, blue.get());
}

TEST(Scene, IsMissedWhenTheRayMissesEveryShape)
{
    Scene scene(whiteLight);
    scene.add(std::make_unique<Sphere>(Vector(5.0, 0.0, 5.0), 1.0, red));
    scene.add(std::make_unique<Plane>(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), blue));

    EXPECT_FALSE(scene.nearestHit(forward).has_value());
}

// A ball resting on a floor: looking down at the ball's top, the ray hits
// the ball before the floor under it; looking down beside it, the floor.
TEST(Scene, MixesSpheresAndPlanes)
{
    Scene scene(whiteLight);
    scene.add(std::make_unique<Plane>(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), blue));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 0.0), 1.0, red));

    const Ray down(Vector(0.0, 5.0, 0.0), Vector(0.0, -1.0, 0.0));
    const std::optional<HitInfo> ball = scene.nearestHit(down);
    ASSERT_TRUE(ball.has_value());
    EXPECT_DOUBLE_EQ(ball->point.y(), 1.0);
    EXPECT_EQ(ball->material, red.get());

    const Ray downBeside(Vector(5.0, 5.0, 0.0), Vector(0.0, -1.0, 0.0));
    const std::optional<HitInfo> floor = scene.nearestHit(downBeside);
    ASSERT_TRUE(floor.has_value());
    EXPECT_DOUBLE_EQ(floor->point.y(), -1.0);
    EXPECT_EQ(floor->material, blue.get());
}

// A shape the Scene has never heard of: every ray hits it, always at the same
// t. The Scene only knows the Shape interface, so it takes new kinds of
// shape without being changed.
class AlwaysHitAtTShape : public Shape {
public:
    AlwaysHitAtTShape(double t, const Material* material) : _t(t), _material(material) {}

    std::optional<HitInfo> hit(const Ray& ray) const override
    {
        return HitInfo{ray.at(_t), Vector(0.0, 0.0, -1.0), _material, _t};
    }

private:
    double _t;
    const Material* _material;
};

TEST(Scene, WorksWithAnyKindOfShape)
{
    Scene scene(whiteLight);
    scene.add(std::make_unique<AlwaysHitAtTShape>(7.0, blue.get()));
    scene.add(std::make_unique<AlwaysHitAtTShape>(2.0, red.get()));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, blue));

    const std::optional<HitInfo> hit = scene.nearestHit(forward);

    ASSERT_TRUE(hit.has_value());
    EXPECT_DOUBLE_EQ(hit->t, 2.0);
    EXPECT_EQ(hit->material, red.get());
}
