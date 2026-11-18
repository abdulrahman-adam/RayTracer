#include <gtest/gtest.h>

#include <cstddef>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

#include <lodepng.h>

#include "image/image.hpp"
#include "io/png_saver.hpp"

namespace {

// A PNG path in the system temp directory, removed when the test ends.
class TempPng {
public:
    explicit TempPng(const std::string& name)
        : _path(std::filesystem::temp_directory_path() / name)
    {
    }
    ~TempPng() { std::filesystem::remove(_path); }

    std::string path() const { return _path.string(); }

private:
    std::filesystem::path _path;
};

} // namespace

TEST(PngSaver, WritesPixelsThatDecodeBackToTheImage)
{
    raytracer::Image image(5, 4);
    image.setPixel(3, 2, raytracer::Colour(1.0, 0.5, 0.0));
    TempPng file("raytracer_png_saver_test.png");

    raytracer::PngSaver saver;
    saver.save(image, file.path());

    std::vector<unsigned char> rgba;
    unsigned width = 0;
    unsigned height = 0;
    ASSERT_EQ(lodepng::decode(rgba, width, height, file.path()), 0u);
    ASSERT_EQ(width, 5u);
    ASSERT_EQ(height, 4u);

    const std::size_t set = (2 * 5 + 3) * 4; // pixel (3, 2)
    EXPECT_EQ(rgba[set + 0], 255);
    EXPECT_EQ(rgba[set + 1], 128);
    EXPECT_EQ(rgba[set + 2], 0);
    EXPECT_EQ(rgba[set + 3], 255);

    EXPECT_EQ(rgba[0], 0); // pixel (0, 0) stays black
    EXPECT_EQ(rgba[1], 0);
    EXPECT_EQ(rgba[2], 0);
    EXPECT_EQ(rgba[3], 255);
}

TEST(PngSaver, ClampsComponentsOutsideZeroToOne)
{
    raytracer::Image image(1, 1);
    image.setPixel(0, 0, raytracer::Colour(-0.5, 0.25, 5.0));
    TempPng file("raytracer_png_saver_clamp_test.png");

    raytracer::PngSaver saver;
    saver.save(image, file.path());

    std::vector<unsigned char> rgba;
    unsigned width = 0;
    unsigned height = 0;
    ASSERT_EQ(lodepng::decode(rgba, width, height, file.path()), 0u);

    EXPECT_EQ(rgba[0], 0);
    EXPECT_EQ(rgba[1], 64);
    EXPECT_EQ(rgba[2], 255);
}

TEST(PngSaver, ThrowsWhenTheFileCannotBeWritten)
{
    raytracer::Image image(1, 1);
    const std::string path =
        (std::filesystem::temp_directory_path() / "no_such_dir_raytracer" / "out.png").string();

    raytracer::PngSaver saver;
    EXPECT_THROW(saver.save(image, path), std::runtime_error);
}
