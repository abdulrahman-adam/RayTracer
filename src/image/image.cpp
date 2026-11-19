#include "image/image.hpp"

#include <cstddef>

Image::Image(unsigned int width, unsigned int height)
    : _width(width),
      _height(height),
      _pixels(static_cast<std::size_t>(width) * height, Colour(0.0, 0.0, 0.0))
{
}

unsigned int Image::width() const
{
    return _width;
}

unsigned int Image::height() const
{
    return _height;
}

void Image::setPixel(unsigned int x, unsigned int y, const Colour& colour)
{
    _pixels[static_cast<std::size_t>(y) * _width + x] = colour;
}

const Colour& Image::pixel(unsigned int x, unsigned int y) const
{
    return _pixels[static_cast<std::size_t>(y) * _width + x];
}
