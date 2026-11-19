#include "camera/camera.hpp"

#include <optional>

Camera::Camera(const Vector& position, double screenWidth)
    : _position(position), _screenWidth(screenWidth)
{
}

const Vector& Camera::position() const
{
    return _position;
}

Ray Camera::rayThroughCenter() const
{
    Vector direction(0,0,1); //Assuming the camera looks along z_axis
    return Ray(_position, direction);
}

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const
{
    // Pixels are square, so the screen height follows from the image's shape.
    const double pixelSize = _screenWidth / imageWidth;
    const double screenHeight = pixelSize * imageHeight;

    // Centre of the pixel on the screen. Screen x grows to the right and
    // y grows up, while image rows grow down, so y is flipped.
    const double x = (column + 0.5) * pixelSize - _screenWidth / 2.0;
    const double y = screenHeight / 2.0 - (row + 0.5) * pixelSize;

    // The screen is 1 unit in front of the camera, along the positive Z-axis.
    Vector direction(x, y, 1.0);
    return Ray(_position, direction);
}

void Camera::render(const Sphere& sphere, const Light& light, Image& image) const
{
    const int imageWidth = static_cast<int>(image.width());
    const int imageHeight = static_cast<int>(image.height());

    for (int row = 0; row < imageHeight; ++row) {
        for (int column = 0; column < imageWidth; ++column) {
            const Ray ray = rayThroughPixel(column, row, imageWidth, imageHeight);

            const std::optional<HitInfo> hit = sphere.hit(ray);
            const Colour colour = hit ? hit->material->shade(*hit, light) : Colour(0, 0, 0);

            image.setPixel(static_cast<unsigned int>(column), static_cast<unsigned int>(row), colour);
        }
    }
}
