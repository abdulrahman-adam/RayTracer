# 9. Shapes behind a Shape interface, owned by a Scene

## Context

The first renderer drew a single `Sphere`: `Camera::render` took a sphere and a light. To draw a ball on a floor, the renderer needs several shapes of different kinds (`Sphere`, `Plane`, and more later), and it has to find the nearest one along each ray.

Alternatives:

- **One list per kind of shape** (`std::vector<Sphere>`, `std::vector<Plane>`) in the scene. No virtual calls, but every new kind of shape means changing the scene and the code that searches it.
- **A `std::variant<Sphere, Plane>`.** Also no virtual calls, but the variant, and every visitor over it, changes with each new shape.
- **An abstract `Shape` class** with one pure virtual method, `hit(ray)`, that `Sphere` and `Plane` implement. The scene holds shapes through pointers to `Shape`.

## Decision

We use an abstract `Shape` class, and a `Scene` that owns the shapes.

- `Shape` (`src/geometry/shape.hpp`) has a virtual destructor and one method: `std::optional<HitInfo> hit(const Ray& ray) const`. It is the only thing the rest of the engine knows about a shape.
- `HitInfo` carries the ray parameter `t` of the hit, so hits from different shapes on the same ray can be compared.
- `Scene` (`src/scene/scene.hpp`) holds the light and a `std::vector<std::unique_ptr<Shape>>`. `add(std::unique_ptr<Shape>)` gives it ownership of a shape. `nearestHit(ray)` returns the hit with the smallest `t`, or `std::nullopt`.
- `trace(ray, scene)` (`src/trace/trace.hpp`) is a free function: the nearest hit, shaded by its material with the scene's light, or black.
- `Camera::render(scene, image)` builds one ray per pixel and calls `trace`.

## Status

Proposed

## Consequences

- A new kind of shape is a new `Shape` subclass. `Scene`, `trace` and `Camera` do not change (open/closed principle). The scene tests check this with a stand-in shape defined in the test file.
- Each class has one job. A shape knows how a ray hits it, the scene knows which hit is nearest, `trace` turns a ray into a colour, and the camera turns pixels into rays.
- `nearestHit` tests every shape for every ray. That is fine for a few shapes, but large scenes will need an acceleration structure, such as a bounding volume hierarchy.
- Each shape is reached through a virtual call.
- The scene cannot be copied, because it owns its shapes through `std::unique_ptr`.
