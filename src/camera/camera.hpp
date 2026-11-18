#pragma once

#include "geometry/sphere.hpp"
#include "image/image.hpp"
#include "math/vector.hpp"
#include "ray/ray.hpp"

namespace raytracer {

// A camera placed at a point in 3D space.
// For now it always looks along the positive Z-axis.
class Camera {
public:
    // Creates a camera at `position`, facing the positive Z-axis.
    // The screen is `screenWidth` units wide and 1 unit in front of the camera.
    Camera(const Vector& position, double screenWidth);

    // Read-only access to the position.
    const Vector& position() const;

    // A ray from the camera position along the positive Z-axis.
    Ray rayThroughCenter() const;

    // A ray from the camera position through the centre of pixel
    // (`column`, `row`) of an image `imageWidth` x `imageHeight` pixels
    // spread over the screen. Pixel (0, 0) is the top-left corner.
    // The direction is not normalised: its z component is always 1.
    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    // Renders `sphere` into `image`, one ray per pixel: pixels whose ray
    // hits the sphere become red, the others black.
    void render(const Sphere& sphere, Image& image) const;

private:
    Vector _position;
    double _screenWidth;
};

} // namespace raytracer
