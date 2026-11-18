#pragma once

#include "math/vector.hpp"
#include "ray/ray.hpp"

namespace raytracer {

// A camera placed at a point in 3D space.
// For now it always looks along the positive Z-axis.
class Camera {
public:
    // Creates a camera at `position`, facing the positive Z-axis.
    explicit Camera(const Vector& position);

    // Read-only access to the position.
    const Vector& position() const;

    // A ray from the camera position along the positive Z-axis.
    Ray rayThroughCenter() const;

private:
    Vector _position;
};

} // namespace raytracer
