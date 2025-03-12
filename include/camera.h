#ifndef CAMERA_H
#define CAMERA_H

#include <chrono>

#include "hittable.h"
#include "material.h"

/**
 * Camera class responsible for generating rays and rendering the scene
 * Controls viewport, lens properties, and handles the rendering process
 */
class camera {
 public:
  // Image properties
  double aspectRatio = 16.0 / 9.0;  // Ratio of image width to height
  int imageWidth = 2560;             // Rendered image width in pixels
  int samplesPerPixel = 10;          // Number of random samples per pixel
  int maxDepth = 10;                 // Maximum number of ray bounces

  // Camera view properties
  double vfov = 90;                  // Vertical field of view in degrees
  point3 lookFrom = point3(0, 0, 0); // Camera position
  point3 lookAt = point3(0, 0, -1);  // Point camera is looking at
  vec3 vup = vec3(0, 1, 0);          // Camera-relative "up" direction

  // Defocus blur (depth of field) properties
  double defocusAngle = 0;           // Variation angle of rays through each pixel
  double focusDist = 10;             // Distance from camera to plane of perfect focus

  /**
   * Render the scene to an output stream
   * Outputs in PPM format, which consists of:
   * - P3 header (indicates ASCII PPM format)
   * - Image dimensions
   * - Max color value (255)
   * - Followed by RGB triplets for each pixel
   * 
   * @param world The collection of objects in the scene
   */
  void render(const hittable &world) {
    // Prepare camera geometry and pixel layout
    initialize();

    // Output PPM header
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    
    // Render each pixel of the image
    for (int j = 0; j < imageHeight; j++) {
      // Display progress
      std::clog << "\rScanlines remaining: " << (imageHeight - j) << " "
                << std::flush;
                
      for (int i = 0; i < imageWidth; i++) {
        // Initialize pixel color to black
        color pixelColor(0, 0, 0);
        
        // Antialiasing: sample multiple rays per pixel
        for (int s = 0; s < samplesPerPixel; s++) {
          ray r = getRay(i, j);
          pixelColor += rayColor(r, maxDepth, world);
        }
        
        // Write the pixel color with scaling for sample count
        writeColor(std::cout, pixelColor * pixelSamplesScale);
      }
    }
    
    // Render complete
    std::clog << "\rDone" << std::endl;
  }

 private:
  // Derived camera properties calculated in initialize()
  int imageHeight;           // Rendered image height (derived from width and aspect ratio)
  point3 origin;             // Camera origin (same as lookFrom)
  point3 pixel00Loc;         // Location of top-left pixel
  vec3 pixelDeltaU;          // Offset to pixel to the right
  vec3 pixelDeltaV;          // Offset to pixel below
  double pixelSamplesScale;  // Scale factor for sample averaging (1/samplesPerPixel)
  
  // Camera basis vectors (forms a coordinate system)
  vec3 u, v, w;              // Camera's orthonormal basis vectors
  
  // Defocus disk geometry
  vec3 defocusDiskU;         // Horizontal component of defocus disk
  vec3 defocusDiskV;         // Vertical component of defocus disk

  /**
   * Initialize camera geometry and calculate derived values
   * Sets up the viewport, pixel locations, and camera orientation
   */
  void initialize() {
    // Calculate image height from aspect ratio
    imageHeight = std::max(static_cast<int>(imageWidth / aspectRatio), 1);

    // Calculate scaling factor for sample averaging
    pixelSamplesScale = 1.0 / samplesPerPixel;

    // Set camera origin
    origin = lookFrom;

    // Calculate viewport dimensions
    auto theta = degreesToRadians(vfov);
    auto h = std::tan(theta / 2);
    auto viewportHeight = 2 * h * focusDist;
    auto viewportWidth =
        viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

    // Calculate camera basis vectors (local coordinate system)
    w = unitVector(lookFrom - lookAt);  // Points from lookAt to camera (camera's forward)
    u = unitVector(cross(vup, w));      // Camera's right vector
    v = cross(w, u);                    // Camera's up vector

    // Calculate viewport vectors
    auto viewportU = viewportWidth * u;    // Viewport width in world space
    auto viewportV = viewportHeight * -v;  // Viewport height in world space (negative because y increases downward in image)

    // Calculate pixel delta vectors
    pixelDeltaU = viewportU / imageWidth;   // Distance between horizontal pixels
    pixelDeltaV = viewportV / imageHeight;  // Distance between vertical pixels

    // Calculate top-left pixel location
    auto viewportUpperLeft =
        origin - (focusDist * w) - viewportU / 2 - viewportV / 2;
    pixel00Loc = viewportUpperLeft + 0.5 * pixelDeltaU + 0.5 * pixelDeltaV;

    // Calculate defocus disk basis vectors
    auto defocusRadius =
        focusDist * std::tan(degreesToRadians(defocusAngle / 2));
    defocusDiskU = u * defocusRadius;  // Horizontal radius of defocus disk
    defocusDiskV = v * defocusRadius;  // Vertical radius of defocus disk
  }

  /**
   * Get a ray from the camera through a specific pixel
   * Implements antialiasing by randomizing the ray origin (defocus blur)
   * and the ray target (jittering within the pixel)
   * 
   * @param i Horizontal pixel index
   * @param j Vertical pixel index
   * @return Ray from camera through the pixel
   */
  ray getRay(int i, int j) {
    // Get random offset within the pixel for antialiasing
    auto offset = sampleSquare();
    
    // Calculate the point on the viewport for this pixel
    auto pixelSample = pixel00Loc + (i + offset.x()) * pixelDeltaU +
                       (j + offset.y()) * pixelDeltaV;
    
    // Determine ray origin (either at camera center or on defocus disk)
    auto rayOrigin = (defocusAngle <= 0) ? origin : defocusDiskSample();
    
    // Create and return the ray
    return ray(rayOrigin, pixelSample - rayOrigin);
  }

  /**
   * Generate a random point within a unit square centered at the origin
   * Used for pixel jittering in antialiasing
   * 
   * @return Point within [-0.5,0.5] × [-0.5,0.5]
   */
  vec3 sampleSquare() {
    return vec3(randomDouble(-0.5, 0.5), randomDouble(-0.5, 0.5), 0);
  }

  /**
   * Generate a random point on the defocus disk
   * Used for simulating depth of field
   * 
   * @return Point on the defocus disk
   */
  point3 defocusDiskSample() {
    auto p = randomInUnitDisk();
    return origin + defocusDiskU * p.x() + defocusDiskV * p.y();
  }

  /**
   * Calculate the color for a ray
   * Handles ray-world intersection, material scattering, and background color
   * Implements recursive ray tracing with a maximum depth
   * 
   * @param r The ray to trace
   * @param depth Maximum number of bounces remaining
   * @param world The scene to trace rays against
   * @return Color value for this ray
   */
  color rayColor(const ray &r, int depth, const hittable &world) {
    // If we've reached the ray bounce limit, return black (no more light)
    if (depth <= 0) return color(0, 0, 0);
    
    hitRecord rec;
    // Check for ray intersection with the scene, ignoring hits very near the ray origin
    if (world.hit(r, interval(0.001, INF), rec)) {
      ray scattered;
      color attenuation;
      
      // Let the material determine how the ray scatters
      if (rec.mat->scatter(r, rec, attenuation, scattered)) {
        // Recursive call for the scattered ray
        return attenuation * rayColor(scattered, depth - 1, world);
      }
      
      // If no scattering occurs, the ray is absorbed and we return black
      return color(0, 0, 0);
    }
    
    // If no hit, return the background color (simple gradient)
    vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);  // Scale y component to [0,1]
    
    // Linear interpolation between white and light blue based on y coordinate
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};

#endif
