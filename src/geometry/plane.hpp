#pragma once

#include <memory>
#include <optional>

#include "geometry/hit_info.hpp"
#include "geometry/shape.hpp"
#include "material/material.hpp"
#include "math/vector.hpp"
#include "ray/ray.hpp"

// An infinite flat surface in 3D space, given by any point on it, the
// direction it faces (its normal) and the material that decides its colour.
// For example, a floor is a plane facing up, (0, 1, 0).
class Plane : public Shape {
public:
    // Creates the plane through `point` facing `normal`, with `material`.
    // The normal is stored with length 1, so it may be given at any length
    // except zero. The material is shared, so several shapes can use it.
    Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material);

    // Read-only access to the point, the normal (length 1) and the material.
    const Vector& point() const;
    const Vector& normal() const;
    const Material& material() const;

    // Where `ray` hits the plane, with the plane's normal and material.
    // Returns std::nullopt when the ray runs parallel to the plane, or when
    // the plane is behind it.
    std::optional<HitInfo> hit(const Ray& ray) const override;

private:
    Vector _point;
    Vector _normal;
    std::shared_ptr<const Material> _material;
};
