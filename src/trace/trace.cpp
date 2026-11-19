#include "trace/trace.hpp"

#include <optional>

#include "geometry/hit_info.hpp"
#include "material/material.hpp"

// The colour of a ray that hits nothing.
static const Colour background(0.0, 0.0, 0.0);

Colour trace(const Ray& ray, const Scene& scene)
{
    const std::optional<HitInfo> hit = scene.nearestHit(ray);
    if (!hit) {
        return background;
    }
    return hit->material->shade(*hit, scene.light());
}
