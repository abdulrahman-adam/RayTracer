#pragma once

#include <optional>

#include "geometry/hit_info.hpp"
#include "ray/ray.hpp"

// Anything a ray can hit. Each kind of shape is its own subclass (see
// Sphere and Plane), so the Scene can hold any of them and new shapes can be
// added without changing the code that traces rays.
class Shape {
public:
    virtual ~Shape() = default;

    // Where `ray` first hits the shape (at the closest non-negative t), with
    // the outward normal there and the shape's material. Returns
    // std::nullopt when the ray misses, or when the shape is behind it.
    virtual std::optional<HitInfo> hit(const Ray& ray) const = 0;
};
