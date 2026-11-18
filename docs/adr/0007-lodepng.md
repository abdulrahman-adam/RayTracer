# 7. Use LodePNG to encode PNG images

## Context

The ray tracer renders into an `Image` (a grid of `Colour`s) and needs to save it to disk. Saving goes through the `ImageSaver` interface, and the first format is PNG (`PngSaver`). PNG needs DEFLATE compression and CRC checksums, which we do not want to write ourselves.

After surveying the available libraries, the team chose LodePNG.

Alternatives:

- **stb_image_write.** Public domain / MIT, a single header. A C-style API.
- **libpng.** The reference PNG library, with the most features. It depends on zlib, which makes it harder to build on Windows.
- **libspng.** Modern and fast, BSD-2. It also depends on zlib.

> **TODO: record the team's reasons for preferring LodePNG over the alternatives.**

## Decision

We use LodePNG (zlib license) to encode PNG files.

- The top-level `CMakeLists.txt` downloads LodePNG at configure time with `FetchContent`, as ADR 0003 does for GoogleTest. Nothing has to be installed.
- LodePNG has no release tags, so we pin it to a commit (`7b2893e35891c0c85bee5595caafaf3c2044b409`) and check the archive with a SHA-256 hash.
- LodePNG ships no `CMakeLists.txt`. We build `lodepng.cpp` into a static `lodepng` target ourselves and mark its include directory `SYSTEM`, so our warning flags are not applied to its header.
- `raytracer_core` links `lodepng` privately; only `src/io/png_saver.cpp` uses it. `raytracer_tests` also links it, to decode saved files and check their pixels.

## Status

Proposed

## Consequences

- PNG encoding needs no system packages, on Windows or in the dev container.
- The pinned commit and hash mean every machine builds the same LodePNG.
- The first configure needs network access to download LodePNG.
- Updating LodePNG means changing both the commit in the URL and the hash.
- GitHub generates commit archives on demand; if one is ever regenerated with different bytes, the hash check fails and the hash must be updated.
