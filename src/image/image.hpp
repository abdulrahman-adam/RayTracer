#pragma once

#include <vector>

#include "colour/colour.hpp"

namespace raytracer {

// A grid of pixels, `width` columns by `height` rows.
// Pixel (0, 0) is the top-left corner; x grows to the right, y grows down.
// Every pixel starts black.
class Image {
public:
    // Creates a black image of the given size.
    Image(unsigned int width, unsigned int height);

    // Read-only access to the size.
    unsigned int width() const;
    unsigned int height() const;

    // Sets the pixel at column `x`, row `y`.
    void setPixel(unsigned int x, unsigned int y, const Colour& colour);

    // Read-only access to the pixel at column `x`, row `y`.
    const Colour& pixel(unsigned int x, unsigned int y) const;

private:
    unsigned int _width;
    unsigned int _height;
    std::vector<Colour> _pixels; // row by row, starting at the top-left
};

} // namespace raytracer
