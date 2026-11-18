#include "camera/camera.hpp"

namespace raytracer {

Camera::Camera(const Vector& position)
    : _position(position)
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

} // namespace raytracer
