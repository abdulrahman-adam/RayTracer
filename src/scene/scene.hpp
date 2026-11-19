#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "geometry/hit_info.hpp"
#include "geometry/shape.hpp"
#include "light/light.hpp"
#include "ray/ray.hpp"

// Everything there is to see: the shapes, and the light that shines on them.
// The scene owns its shapes. It only knows them as Shapes, so any kind of
// shape can be added without changing the scene.
class Scene {
public:
    // Creates an empty scene lit by `light`.
    explicit Scene(const Light& light);

    // Read-only access to the light.
    const Light& light() const;

    // Adds `shape` to the scene, which takes ownership of it.
    void add(std::unique_ptr<Shape> shape);

    // The hit nearest the ray's origin (the smallest t) among all the shapes.
    // Returns std::nullopt when the ray hits no shape. A HitInfo points at
    // its shape's material, so it must not outlive the scene.
    std::optional<HitInfo> nearestHit(const Ray& ray) const;

private:
    Light _light;
    std::vector<std::unique_ptr<Shape>> _shapes;
};
