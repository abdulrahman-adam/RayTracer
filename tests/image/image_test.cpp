#include <gtest/gtest.h>

#include <string>

#include "image/image.hpp"

TEST(Image, StoresWidthAndHeight)
{
    raytracer::Image image(5, 4);

    EXPECT_EQ(image.width(), 5u);
    EXPECT_EQ(image.height(), 4u);
}

TEST(Image, SetPixelSetsOnlyThatColumnAndRow)
{
    raytracer::Image image(5, 4);

    image.setPixel(3, 2, raytracer::Colour(1.0, 0.5, 0.25));

    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            const raytracer::Colour& pixel = image.pixel(x, y);
            SCOPED_TRACE("pixel (" + std::to_string(x) + ", " + std::to_string(y) + ")");

            if (x == 3 && y == 2) {
                EXPECT_DOUBLE_EQ(pixel.r(), 1.0);
                EXPECT_DOUBLE_EQ(pixel.g(), 0.5);
                EXPECT_DOUBLE_EQ(pixel.b(), 0.25);
            } else {
                EXPECT_DOUBLE_EQ(pixel.r(), 0.0);
                EXPECT_DOUBLE_EQ(pixel.g(), 0.0);
                EXPECT_DOUBLE_EQ(pixel.b(), 0.0);
            }
        }
    }
}
