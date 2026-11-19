#pragma once

#include <memory>
#include <optional>

#include "geometry/hit_info.hpp"
#include "geometry/shape.hpp"
#include "material/material.hpp"
#include "math/vector.hpp"
#include "ray/ray.hpp"

// A sphere in 3D space, given by its center point, its radius and the
// material that decides its colour.
class Sphere : public Shape {
public:
    // Creates a sphere centered at `center` with the given `radius` and `material`.
    // The material is shared, so several spheres can use the same one.
    Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material);

    // Read-only access to the center, radius and material.
    const Vector& center() const;
    double radius() const;
    const Material& material() const;

    // Where `ray` first hits the sphere (at the closest non-negative t), with
    // the outward normal there and the sphere's material. Returns
    // std::nullopt when the ray misses, or when the sphere is behind it.
    std::optional<HitInfo> hit(const Ray& ray) const override;

private:
    Vector _center;
    double _radius;
    std::shared_ptr<const Material> _material;
};
