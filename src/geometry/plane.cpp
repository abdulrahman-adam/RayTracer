#include "geometry/plane.hpp"

#include <cmath>
#include <utility>

// Below this, the ray is treated as parallel to the plane: it would only
// meet it infinitely far away, or numerically unstably close to that.
static constexpr double parallelTolerance = 1e-12;

Plane::Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material)
    : _point(point), _normal(normal.normalised()), _material(std::move(material))
{
}

const Vector& Plane::point() const
{
    return _point;
}

const Vector& Plane::normal() const
{
    return _normal;
}

const Material& Plane::material() const
{
    return *_material;
}

std::optional<HitInfo> Plane::hit(const Ray& ray) const
{
    // A point P is on the plane when N . (P - point) = 0. Putting the ray
    // P = O + t * D in that gives t = N . (point - O) / (N . D).
    const double denominator = _normal.dot(ray.direction());
    if (std::abs(denominator) < parallelTolerance) {
        return std::nullopt; // The ray runs parallel to the plane.
    }

    const double t = _normal.dot(_point - ray.origin()) / denominator;
    if (t < 0) {
        return std::nullopt; // The plane is behind the ray.
    }

    return HitInfo{ray.at(t), _normal, _material.get(), t};
}
