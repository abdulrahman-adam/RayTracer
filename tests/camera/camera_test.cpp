#include <gtest/gtest.h>

#include "camera/camera.hpp"

TEST(Camera, StoresPosition)
{
    raytracer::Camera camera(raytracer::Vector(1.0, 2.0, 3.0));

    EXPECT_DOUBLE_EQ(camera.position().x(), 1.0);
    EXPECT_DOUBLE_EQ(camera.position().y(), 2.0);
    EXPECT_DOUBLE_EQ(camera.position().z(), 3.0);
}

TEST(Camera, RayThroughCenterStartsAtCameraPosition)
{
    raytracer::Camera camera(raytracer::Vector(1.0, 2.0, 3.0));

    raytracer::Ray ray = camera.rayThroughCenter();

    EXPECT_DOUBLE_EQ(ray.origin().x(), 1.0);
    EXPECT_DOUBLE_EQ(ray.origin().y(), 2.0);
    EXPECT_DOUBLE_EQ(ray.origin().z(), 3.0);
}

TEST(Camera, RayThroughCenterPointsAlongPositiveZ)
{
    raytracer::Camera camera(raytracer::Vector(1.0, 2.0, 3.0));

    raytracer::Ray ray = camera.rayThroughCenter();

    EXPECT_DOUBLE_EQ(ray.direction().x(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().y(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction().z(), 1.0);
}
