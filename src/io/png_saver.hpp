#pragma once

#include <string>

#include "io/image_saver.hpp"

// Saves an image to disk as a PNG file, using LodePNG.
class PngSaver : public ImageSaver {
public:
    // Encodes `image` as an 8-bit RGBA PNG and writes it to `path`.
    // Colour components are clamped to [0, 1] and scaled to 0-255.
    // Throws std::runtime_error if encoding or writing fails.
    void save(Image& image, const std::string& path) override;
};
