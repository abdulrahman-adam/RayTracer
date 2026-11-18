#pragma once

#include <string>

#include "image/image.hpp"

namespace raytracer {

// Saves an image to a file on disk.
// Each output format is its own subclass (see PngSaver).
class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    // Saves `image` to the file at `path`.
    virtual void save(Image& image, const std::string& path) = 0;
};

} // namespace raytracer
