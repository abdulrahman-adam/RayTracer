#include <gtest/gtest.h>

#include <memory>

#include "camera/camera.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "light/light.hpp"
#include "material/flat_shader.hpp"
#include "material/lambert_shader.hpp"
#include "scene/scene.hpp"
#include "test_helpers.hpp"

TEST(Camera, StoresPosition)
{
    Camera camera(Vector(1.0, 2.0, 3.0), 5.0);

    expectVector(camera.position(), 1.0, 2.0, 3.0);
}

// Scenario for rayThroughPixel: a screen 5 units wide, one unit in front of
// the camera, and an image of 5 columns by 3 rows, so each pixel is 1 unit.
// Pixel (0, 0) is the top-left; screen x grows right and y grows up.

constexpr double screenWidth = 5.0;
constexpr int imageWidth = 5;
constexpr int imageHeight = 3;

static void expectDirection(const Ray& ray, double x, double y, double z)
{
    expectVector(ray.direction(), x, y, z);
}

TEST(Camera, RayThroughCenterPixelPointsStraightAhead)
{
    Camera camera(Vector(0.0, 0.0, 0.0), screenWidth);

    Ray ray = camera.rayThroughPixel(2, 1, imageWidth, imageHeight);

    expectDirection(ray, 0.0, 0.0, 1.0);
}

TEST(Camera, RayThroughTopRightPixelPointsUpAndRight)
{
    Camera camera(Vector(0.0, 0.0, 0.0), screenWidth);

    Ray ray = camera.rayThroughPixel(4, 0, imageWidth, imageHeight);

    expectDirection(ray, 2.0, 1.0, 1.0);
}

TEST(Camera, RayThroughBottomLeftPixelPointsDownAndLeft)
{
    Camera camera(Vector(0.0, 0.0, 0.0), screenWidth);

    Ray ray = camera.rayThroughPixel(0, 2, imageWidth, imageHeight);

    expectDirection(ray, -2.0, -1.0, 1.0);
}

TEST(Camera, RayThroughPixelStartsAtCameraPosition)
{
    Camera camera(Vector(1.0, 2.0, 3.0), screenWidth);

    Ray ray = camera.rayThroughPixel(4, 0, imageWidth, imageHeight);

    EXPECT_DOUBLE_EQ(ray.origin().x(), 1.0);
    EXPECT_DOUBLE_EQ(ray.origin().y(), 2.0);
    EXPECT_DOUBLE_EQ(ray.origin().z(), 3.0);
}

// A non-square image with pixels smaller than one unit: a screen 2 units
// wide over 512 x 256 pixels gives pixels 2 / 512 = 1/256 units wide, and a
// screen 256 / 256 = 1 unit tall. Ray directions aim at pixel centres, half a
// pixel (1/512) in from each edge of the screen.
TEST(Camera, RayThroughPixelScalesToPixelSize)
{
    Camera camera(Vector(0.0, 0.0, 0.0), 2.0);
    const double halfPixel = 1.0 / 512.0;

    // Top-left pixel: just inside the screen's left edge (x = -1) and top edge (y = 0.5).
    expectDirection(camera.rayThroughPixel(0, 0, 512, 256), -1.0 + halfPixel, 0.5 - halfPixel, 1.0);

    // Bottom-right pixel: just inside the right edge (x = 1) and bottom edge (y = -0.5).
    expectDirection(camera.rayThroughPixel(511, 255, 512, 256), 1.0 - halfPixel, -0.5 + halfPixel, 1.0);
}

// render: a 5 x 3 image over a screen 5 units wide, and a sphere of radius 1
// straight ahead at z = 5. Only the centre pixel's ray, (0, 0, 1), hits it;
// the corner rays, e.g. (2, 1, 1), pass far outside.

TEST(Camera, RenderShadesHitPixelsWithTheShapeMaterialAndMissedPixelsBlack)
{
    Camera camera(Vector(0.0, 0.0, 0.0), 5.0);
    Scene scene(Light(Vector(0.0, 0.0, 0.0), white));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0,
                                       std::make_shared<FlatShader>(Colour(1.0, 1.0, 0.0))));
    Image image(5, 3);

    camera.render(scene, image);

    expectColour(image.pixel(2, 1), 1.0, 1.0, 0.0); // centre
    expectColour(image.pixel(4, 0), 0.0, 0.0, 0.0); // top-right
}

// Same scene with a Lambert sphere, to check render shades with the hit and
// the scene's light. The centre ray hits (0, 0, 4), where the normal is
// (0, 0, -1). A light at the camera faces it head on (full colour); a light
// behind the sphere leaves it black.
TEST(Camera, RenderShadesWithTheHitAndTheSceneLight)
{
    Camera camera(Vector(0.0, 0.0, 0.0), 5.0);
    const auto matte = std::make_shared<LambertShader>(Colour(1.0, 0.5, 0.25));
    Image image(5, 3);

    Scene litFromFront(Light(Vector(0.0, 0.0, 0.0), white));
    litFromFront.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, matte));
    camera.render(litFromFront, image);
    expectColour(image.pixel(2, 1), 1.0, 0.5, 0.25);

    Scene litFromBehind(Light(Vector(0.0, 0.0, 10.0), white));
    litFromBehind.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, matte));
    camera.render(litFromBehind, image);
    expectColour(image.pixel(2, 1), 0.0, 0.0, 0.0);
}

// A ball on a floor. The floor is the plane y = -0.5, facing up. The bottom
// row's rays point down, e.g. (-2, -1, 1), so they hit the floor; the middle
// row's rays are level with it and the top row's point up, so they miss it.
// The centre ray still hits the ball.
TEST(Camera, RenderShowsEveryShapeInTheScene)
{
    Camera camera(Vector(0.0, 0.0, 0.0), 5.0);
    Scene scene(Light(Vector(0.0, 0.0, 0.0), white));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0,
                                       std::make_shared<FlatShader>(Colour(1.0, 1.0, 0.0))));
    scene.add(std::make_unique<Plane>(Vector(0.0, -0.5, 0.0), Vector(0.0, 1.0, 0.0),
                                      std::make_shared<FlatShader>(Colour(0.5, 0.5, 0.5))));
    Image image(5, 3);

    camera.render(scene, image);

    expectColour(image.pixel(2, 1), 1.0, 1.0, 0.0); // centre: the ball
    expectColour(image.pixel(0, 2), 0.5, 0.5, 0.5); // bottom-left: the floor
    expectColour(image.pixel(4, 2), 0.5, 0.5, 0.5); // bottom-right: the floor
    expectColour(image.pixel(0, 1), 0.0, 0.0, 0.0); // middle-left: nothing
    expectColour(image.pixel(4, 0), 0.0, 0.0, 0.0); // top-right: nothing
}
