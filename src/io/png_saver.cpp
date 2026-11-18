#include "io/png_saver.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <vector>

#include <lodepng.h>

namespace raytracer {

namespace {

// Converts a colour component in [0, 1] to a byte in [0, 255].
unsigned char toByte(double component)
{
    const double clamped = std::clamp(component, 0.0, 1.0);
    return static_cast<unsigned char>(std::lround(clamped * 255.0));
}

} // namespace

void PngSaver::save(Image& image, const std::string& path)
{
    const unsigned int width = image.width();
    const unsigned int height = image.height();

    // LodePNG expects RGBA bytes, row by row from the top-left.
    std::vector<unsigned char> rgba;
    rgba.reserve(static_cast<std::size_t>(width) * height * 4);
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            const Colour& colour = image.pixel(x, y);
            rgba.push_back(toByte(colour.r()));
            rgba.push_back(toByte(colour.g()));
            rgba.push_back(toByte(colour.b()));
            rgba.push_back(255);
        }
    }

    const unsigned error = lodepng::encode(path, rgba, width, height);
    if (error != 0) {
        throw std::runtime_error("Failed to save PNG '" + path + "': " + lodepng_error_text(error));
    }
}

} // namespace raytracer
