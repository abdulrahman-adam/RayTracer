# Discovery report

## Problem statement

The client needs to generate realistic images of 3D scenes because believable images require an accurate simulation of light, but existing renderers are either costly and closed or too complex to understand, adapt and extend.

## Client interview summary

> No interview quotes are cited below yet. Each need is labelled as my own conclusion until it is confirmed against the interview notes.

### Rendering realistic scenes

**Need:** Turn a 3D scene (objects, lights, camera) into a realistic image.

**My conclusion:** The first version must support camera rays, basic shapes (sphere, plane), lighting, shadows and reflections.

### Software quality

**Need:** An engine that is modular, tested and easy to extend.

**My conclusion:** Quality matters as much as the image itself. Shapes and materials must be addable without changing the core.

### Performance

**Need:** Render in a reasonable time.

**My conclusion:** Measure first, then optimise (multithreading, acceleration structures).

### Open questions

- How are scenes described (file format), and what image format is expected?
- Which features are mandatory for the first release?
- Is there a render-time or resolution target?
- Are external libraries, multithreading or GPU allowed?

## State of the art

| Solution | Maker | Licence | Pricing (checked 2026-11-16) | Capabilities | Sources |
|---|---|---|---|---|---|
| V-Ray | Chaos | Proprietary | ~$540/year (third-party source) | CPU/GPU, plugins for 3D tools | [chaos.com](https://www.chaos.com/vray), [renderahouse](https://www.renderahouse.com/blog/vray-pricing) |
| Arnold | Autodesk | Proprietary | ~$430/year (reseller) | Path tracer for film/VFX, CPU/GPU | [autodesk.com](https://www.autodesk.com/products/arnold), [motionmedia](https://www.motionmedia.com/autodesk-arnold) |
| KeyShot | KeyShot | Proprietary | $1,299/year | Product visualisation, CPU/GPU | [keyshot.com](https://www.keyshot.com/pricing/) |
| Cycles | Blender Foundation | Apache 2.0 | Free | Path tracer in Blender, CPU/GPU | [blender.org](https://www.blender.org/features/rendering/) |
| pbrt-v4 | Pharr, Jakob, Humphreys | Apache 2.0 | Free | Reference physically based renderer (C++) | [pbrt.org](https://pbrt.org/) |
| Ray Tracing in One Weekend | Shirley et al. | CC0 | Free | Small educational C++ ray tracer | [raytracing.github.io](https://raytracing.github.io/) |

All solutions share the same core: camera rays, intersections and physically based shading. Commercial tools are powerful but expensive and closed. Open-source tools are either very large (Cycles, pbrt) or purely educational. None offers a small, modular, tested engine that the client fully owns and can extend.

## What is ray tracing?

Ray tracing creates an image by casting rays from a camera into a 3D scene. **Input:** objects, materials, lights and a camera. **Output:** an image made of coloured pixels. **Process:** for each pixel, a ray finds the nearest object it hits. The colour is computed from the material and the lights. Shadow rays check visibility to each light, and reflection or refraction rays repeat the process recursively. More rays per pixel give higher quality at a higher computational cost.

**Sources:** Started from [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). Reference: [Physically Based Rendering, 4th ed.](https://pbr-book.org/4ed/contents)

## What is C++?

### Programming paradigms

C++ is multi-paradigm: procedural, object-oriented, generic (templates) and partly functional (lambdas, algorithms). Compared with Python, it is compiled and statically typed, so it is much faster. Compared with Java, it has no garbage collector and does not force everything into classes.

### What to watch out for

The developer manages memory and object lifetimes. Classic traps: dangling pointers, memory leaks, undefined behaviour (out-of-bounds access, uninitialised variables), unnecessary copies and floating-point precision errors. Mitigations: RAII, smart pointers, standard containers, compiler warnings and sanitizers.

### Shaping the domain model

Value types for maths (`Vec3`, `Ray`, `Color`). Interfaces with virtual functions for extensible concepts (`Shape`, `Material`, `Light`). A `Scene` that owns its objects. Separate `Camera`, `Renderer` and image output so each part can be tested on its own.

**Sources:** Started from [learncpp.com](https://www.learncpp.com/). Reference: [cppreference](https://en.cppreference.com/w/cpp) and the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).
