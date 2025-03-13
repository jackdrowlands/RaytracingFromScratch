# Ray Tracing Engine

![Ray Traced Scene](image.ppm)

## Overview

This project is a physically-based ray tracer implemented from scratch in C++. It simulates the behavior of light to generate photorealistic images, capturing complex visual phenomena such as reflection, refraction, shadows, and depth of field.

The implementation follows modern rendering principles, utilizing Monte Carlo methods for anti-aliasing and material simulation. It produces high-quality images by tracing the paths of individual light rays through a scene, accurately modeling how light interacts with different materials.

## Features

- **Physically-based rendering**: Accurate simulation of light behavior following physical laws
- **Multiple material types**:
  - Lambertian (diffuse) surfaces
  - Metallic surfaces with adjustable roughness
  - Dielectric (glass-like) materials with accurate refraction
- **Camera simulation**:
  - Configurable field of view
  - Depth of field effects
  - Adjustable aperture and focus distance
- **Anti-aliasing**: Multi-sample rendering for smooth edges
- **Scene composition**: Programmatic scene creation with various object types

## Technical Implementation

The ray tracer is built around several key components:

- **Vector mathematics**: Custom 3D vector implementation with all necessary operations
- **Ray class**: Core data structure for tracing light paths
- **Hit detection**: Precise intersection calculations for various geometries
- **Material system**: Modular system for simulating different surface types
- **Camera model**: Simulates a realistic camera with configurable parameters
- **Image output**: Renders to PPM format for easy visualization

## Code Architecture

The codebase is organized into modular, reusable components:

```
├── include/              # Header files
│   ├── camera.h          # Camera model with DoF and positioning
│   ├── color.h           # Color handling and output
│   ├── hittable.h        # Abstract base class for scene objects
│   ├── hittableList.h    # Container for managing multiple objects
│   ├── interval.h        # Range utility for ray parameters
│   ├── material.h        # Material definitions and light behavior
│   ├── ray.h             # Core ray structure
│   ├── sphere.h          # Sphere geometry implementation
│   ├── utils.h           # Common utilities and constants
│   └── vec3.h            # Vector mathematics
├── src/
│   └── main.cpp          # Scene definition and rendering pipeline
└── CMakeLists.txt        # Build configuration
```

## Performance Considerations

The renderer uses several optimization techniques:

- **Early ray termination**: Stops tracing when contribution becomes negligible
- **Spatial data structures**: Efficient scene traversal
- **Statistical sampling**: Smart distribution of rays for noise reduction
- **Vectorization**: Core math optimized for modern CPU architectures

## Rendered Results

The example scene demonstrates the ray tracer's capabilities by rendering:

- A large field of random spheres with various materials
- Three feature spheres showcasing different material properties:
  - A central glass sphere with refraction
  - A diffuse brown sphere
  - A polished metal sphere

The high sample count (500 samples per pixel) and recursive depth (50 bounces) produce a high-quality image that accurately captures complex light interactions.

## Build Instructions

1. Ensure you have a C++17 compatible compiler and CMake installed
2. Clone the repository
3. Build with CMake:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Run the ray tracer:
   ```
   ./raytracingInAWeekend > image.ppm
   ```

## Future Enhancements

Potential areas for future development:

- Acceleration structures (BVH, kD-trees) for faster rendering
- Additional primitives (planes, triangles, meshes)
- Texture mapping and normal mapping
- Area lights and soft shadows
- Volumetric effects (fog, smoke)
- Parallelization using multiple threads

## References

This implementation draws inspiration from Peter Shirley's "Ray Tracing in One Weekend" series.