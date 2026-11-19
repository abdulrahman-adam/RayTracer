# 8. A shape has a material

## Context

Every shape the ray tracer draws needs a colour, and the colour depends on how the surface is shaded: a flat colour (`FlatShader`), or a matte surface lit by a light (`LambertShader`). More shading models will come later, such as mirrors and glossy surfaces.

The question is how a shape and its shading are put together.

Alternatives:

- **A colour field on each shape.** It is the simplest, and was our first version (`Sphere` had a `Colour`). But every new way of shading would mean changing every shape.
- **One subclass per shape and shading pair** (`LambertSphere`, `FlatPlane`, ...). The number of classes multiplies with every new shape or material.
- **The shading is decided outside the shapes**, for example by a table from shape to colour in the scene. The shape and its look are then easy to separate by accident, and every lookup has to be kept in sync.
- **A shape has a material** (composition, the Strategy pattern). `Material` is an interface with one method, `shade`. Each shape holds one material and hands it out with every hit.

## Decision

A shape has a material.

- `Material` is an abstract class with `shade(const HitInfo& hit, const Light& light) const`. Each shading model is its own subclass (`FlatShader`, `LambertShader`).
- Each shape (`Sphere`, `Plane`) takes a `std::shared_ptr<const Material>` in its constructor and keeps it. The pointer is shared, so several shapes can use the same material, and `const`, so a shape cannot change it.
- When a ray hits a shape, the `HitInfo` carries a plain `const Material*` to that material. `trace` uses it to shade the hit. The shape keeps the material alive, so a `HitInfo` must not outlive the scene it came from.

## Status

Proposed

## Consequences

- A new shading model is a new `Material` subclass. No shape, nor `Scene`, `trace` or `Camera`, has to change (open/closed principle).
- A new shape only has to pass its material into the hits it returns.
- Shapes and materials can be tested on their own. Shape tests use a `FlatShader`, and material tests build a `HitInfo` by hand.
- The material is reached through a virtual call for every hit, which costs a little speed.
- A `HitInfo` holds a non-owning pointer. Keeping it after the scene is destroyed would leave a dangling pointer.
