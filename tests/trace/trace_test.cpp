#include <gtest/gtest.h>

#include <memory>

#include "colour/colour.hpp"
#include "geometry/sphere.hpp"
#include "light/light.hpp"
#include "material/flat_shader.hpp"
#include "material/lambert_shader.hpp"
#include "ray/ray.hpp"
#include "scene/scene.hpp"
#include "test_helpers.hpp"
#include "trace/trace.hpp"

// All the tests shoot this ray from the origin along +Z. A sphere of radius 1
// at z = 5 is hit at (0, 0, 4), where the normal is (0, 0, -1).
static const Ray forward(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

TEST(Trace, RayHittingNothingGivesBlack)
{
    const Scene scene(Light(Vector(0.0, 0.0, 0.0), white));

    expectColour(trace(forward, scene), 0.0, 0.0, 0.0);
}

TEST(Trace, RayMissingEveryShapeGivesBlack)
{
    Scene scene(Light(Vector(0.0, 0.0, 0.0), white));
    scene.add(std::make_unique<Sphere>(Vector(5.0, 0.0, 5.0), 1.0,
                                       std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0))));

    expectColour(trace(forward, scene), 0.0, 0.0, 0.0);
}

TEST(Trace, RayHittingAShapeGivesItsMaterialColour)
{
    Scene scene(Light(Vector(0.0, 0.0, 0.0), white));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0,
                                       std::make_shared<FlatShader>(Colour(0.25, 0.5, 0.75))));

    expectColour(trace(forward, scene), 0.25, 0.5, 0.75);
}

// Two spheres in a row: the colour comes from the nearer one only.
TEST(Trace, ShadesTheNearestShape)
{
    Scene scene(Light(Vector(0.0, 0.0, 0.0), white));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 10.0), 1.0,
                                       std::make_shared<FlatShader>(Colour(0.0, 0.0, 1.0))));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0,
                                       std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0))));

    expectColour(trace(forward, scene), 1.0, 0.0, 0.0);
}

// A Lambert sphere shows trace hands the material the hit and the scene's
// light: a light at the camera faces the hit point head on (full colour); a
// light behind the sphere leaves it black.
TEST(Trace, ShadesWithTheHitAndTheSceneLight)
{
    const auto matte = std::make_shared<LambertShader>(Colour(1.0, 0.5, 0.25));

    Scene litFromFront(Light(Vector(0.0, 0.0, 0.0), white));
    litFromFront.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, matte));
    expectColour(trace(forward, litFromFront), 1.0, 0.5, 0.25);

    Scene litFromBehind(Light(Vector(0.0, 0.0, 10.0), white));
    litFromBehind.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, matte));
    expectColour(trace(forward, litFromBehind), 0.0, 0.0, 0.0);
}
