#include <gtest/gtest.h>

#include <memory>

#include "camera/camera.hpp"
#include "material/flat_shader.hpp"

TEST(Camera, StoresPosition)
{
    Camera camera(Vector(1.0, 2.0, 3.0), 5.0);

    EXPECT_DOUBLE_EQ(camera.position().x(), 1.0);
    EXPECT_DOUBLE_EQ(camera.position().y(), 2.0);
    EXPECT_DOUBLE_EQ(camera.position().z(), 3.0);
}

TEST(Camera, RayThroughCenterStartsAtCameraPosition)
{
    Camera camera(Vector(1.0, 2.0, 3.0), 5.0);

    Ray ray = camera.rayThroughCenter();

    EXPECT_DOUBLE_EQ(ray.origin().x(), 1.0);
    EXPECT_DOUBLE_EQ(ray.origin().y(), 2.0);
    EXPECT_DOUBLE_EQ(ray.origin().z(), 3.0);
}

TEST(Camera, RayThroughCenterPointsAlongPositiveZ)
{
    Camera camera(Vector(1.0, 2.0, 3.0), 5.0);

    Ray ray = camera.rayThroughCenter();

    EXPECT_DOUBLE_EQ(ray.direction().x(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().y(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().z(), 1.0);
}

// Scenario for rayThroughPixel: a screen 5 units wide, one unit in front of
// the camera, and an image of 5 columns by 3 rows, so each pixel is 1 unit.
// Pixel (0, 0) is the top-left; screen x grows right and y grows up.

constexpr double screenWidth = 5.0;
constexpr int imageWidth = 5;
constexpr int imageHeight = 3;

static void expectDirection(const Ray& ray, double x, double y, double z)
{
    EXPECT_DOUBLE_EQ(ray.direction().x(), x);
    EXPECT_DOUBLE_EQ(ray.direction().y(), y);
    EXPECT_DOUBLE_EQ(ray.direction().z(), z);
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
TEST(Camera, RenderShadesHitPixelsWithSphereMaterialAndMissedPixelsBlack)
{
    Camera camera(Vector(0.0, 0.0, 0.0), 5.0);
    Sphere sphere(Vector(0.0, 0.0, 5.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 1.0, 0.0)));
    Image image(5, 3);

    camera.render(sphere, image);

    const Colour& centre = image.pixel(2, 1);
    EXPECT_DOUBLE_EQ(centre.r(), 1.0);
    EXPECT_DOUBLE_EQ(centre.g(), 1.0);
    EXPECT_DOUBLE_EQ(centre.b(), 0.0);

    const Colour& topRight = image.pixel(4, 0);
    EXPECT_DOUBLE_EQ(topRight.r(), 0.0);
    EXPECT_DOUBLE_EQ(topRight.g(), 0.0);
    EXPECT_DOUBLE_EQ(topRight.b(), 0.0);
}
