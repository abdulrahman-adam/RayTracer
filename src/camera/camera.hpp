#pragma once

#include "image/image.hpp"
#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "scene/scene.hpp"

// A camera placed at a point in 3D space.
// For now it always looks along the positive Z-axis.
class Camera {
public:
    // Creates a camera at `position`, facing the positive Z-axis.
    // The screen is `screenWidth` units wide and 1 unit in front of the camera.
    Camera(const Vector& position, double screenWidth);

    // Read-only access to the position.
    const Vector& position() const;

    // A ray from the camera position through the centre of pixel
    // (`column`, `row`) of an image `imageWidth` x `imageHeight` pixels
    // spread over the screen. Pixel (0, 0) is the top-left corner.
    // The direction is not normalised: its z component is always 1.
    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    // Renders `scene` into `image`, one ray per pixel: each pixel gets the
    // colour trace() sees along its ray, so it shows the nearest shape it
    // hits, shaded by that shape's material, or black if it hits nothing.
    void render(const Scene& scene, Image& image) const;

private:
    Vector _position;
    double _screenWidth;
};
