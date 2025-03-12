#include "../include/hittable.h"
#include "../include/hittableList.h"
#include "../include/sphere.h"
#include "../include/utils.h"
#include "../include/camera.h"

/**
 * Main program that sets up a scene and renders it using ray tracing
 */
int main() {
  // Create an empty scene
  hittableList world;

  // Add a large sphere as the ground
  auto groundMaterial = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, groundMaterial));

  // Generate a random scene with many small spheres
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      // Choose a random material type
      auto chooseMat = randomDouble();
      
      // Create a random center point with small random offset
      point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

      // Ensure spheres aren't too close to the large spheres we'll add later
      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        shared_ptr<material> sphereMaterial;

        if (chooseMat < 0.8) {
          // Diffuse material (80% chance)
          auto albedo = vec3::random() * vec3::random();  // Random color with gamma correction
          sphereMaterial = make_shared<lambertian>(albedo);
          world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
        } else if (chooseMat < 0.95) {
          // Metal material (15% chance)
          auto albedo = vec3::random(0.5, 1);  // Metallic colors tend to be lighter
          auto fuzz = randomDouble(0, 0.5);    // Random fuzziness/roughness
          sphereMaterial = make_shared<metal>(albedo, fuzz);
          world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
        } else {
          // Glass material (5% chance)
          sphereMaterial = make_shared<dielectric>(1.5);  // Index of refraction for glass
          world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
        }
      }
    }
  }

  // Add three large spheres as focal points of the scene
  
  // Large glass sphere in the center
  auto material1 = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  // Large diffuse sphere to the left
  auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));  // Brown
  world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  // Large metal sphere to the right
  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);  // Polished gold
  world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  // Configure the camera
  camera cam;
  
  // Image settings
  cam.aspectRatio = 16.0 / 9.0;    // Widescreen aspect ratio
  cam.imageWidth = 2560;           // High resolution image
  cam.samplesPerPixel = 500;       // High quality antialiasing
  cam.maxDepth = 50;               // Deep recursion for reflections
  
  // Camera position and orientation
  cam.vfov = 20;                   // Narrow field of view for more detail
  cam.lookFrom = point3(13, 2, 3); // Camera positioned above and to the side
  cam.lookAt = point3(0, 0, 0);    // Looking at the origin
  cam.vup = vec3(0, 1, 0);         // "Up" direction is global Y axis
  
  // Depth of field settings
  cam.defocusAngle = 0.6;          // Moderate depth of field effect
  cam.focusDist = 10.0;            // Focus distance to main scene elements

  // Render the scene
  cam.render(world);

  return 0;
}