#ifndef CAMERA_H
#define CAMERA_H

#include <chrono>

#include "hittable.h"
#include "material.h"

class camera {
 public:
  double aspectRatio = 16.0 / 9.0;
  int imageWidth = 2560;
  int samplesPerPixel = 10;
  int maxDepth = 10;

  double vfov = 90;
  point3 lookFrom = point3(0, 0, 0);
  point3 lookAt = point3(0, 0, -1);
  vec3 vup = vec3(0, 1, 0);

  double defocusAngle = 0;
  double focusDist = 10;

  void render(const hittable &world) {
    initialize();

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    for (int i = 0; i < imageHeight; i++) {
      std::clog << "\rScanlines remaining: " << (imageHeight - i) << " "
                << std::flush;
      for (int j = 0; j < imageWidth; j++) {
        color pixelColor(0, 0, 0);
        for (int s = 0; s < samplesPerPixel; s++) {
          ray r = getRay(j, i);
          pixelColor += rayColor(r, maxDepth, world);
        }
        writeColor(std::cout, pixelColor * pixelSamplesScale);
      }
    }
    std::clog << "\rDone" << std::endl;
  }

 private:
  int imageHeight;           // Rendered image height
  point3 origin;             // Camera origin
  point3 pixel00Loc;         // Location of pixel 0, 0
  vec3 pixelDeltaU;          // Offset to pixel to the right
  vec3 pixelDeltaV;          // Offset to pixel below
  double pixelSamplesScale;  // Average number of samples per pixel
  vec3 u, v, w;
  vec3 defocusDiskU;
  vec3 defocusDiskV;

  void initialize() {
    imageHeight = std::max(static_cast<int>(imageWidth / aspectRatio), 1);

    pixelSamplesScale = 1.0 / samplesPerPixel;

    origin = lookFrom;

    auto theta = degreesToRadians(vfov);
    auto h = std::tan(theta / 2);
    auto viewportHeight = 2 * h * focusDist;
    auto viewportWidth =
        viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

    w = unitVector(lookFrom - lookAt);
    u = unitVector(cross(vup, w));
    v = cross(w, u);

    auto viewportU = viewportWidth * u;
    auto viewportV = viewportHeight * -v;

    pixelDeltaU = viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight;

    auto viewportUpperLeft =
        origin - (focusDist * w) - viewportU / 2 - viewportV / 2;
    pixel00Loc = viewportUpperLeft + 0.5 * pixelDeltaU + 0.5 * pixelDeltaV;

    auto defocusRadius =
        focusDist * std::tan(degreesToRadians(defocusAngle / 2));
    defocusDiskU = u * defocusRadius;
    defocusDiskV = v * defocusRadius;
  }

  ray getRay(int i, int j) {
    auto offset = sampleSquare();
    auto pixelSample = pixel00Loc + (i + offset.x()) * pixelDeltaU +
                       (j + offset.y()) * pixelDeltaV;
    auto rayOrigin = (defocusAngle <= 0) ? origin : defocusDiskSample();
    return ray(rayOrigin, pixelSample - rayOrigin);
  }

  vec3 sampleSquare() {
    return vec3(randomDouble(-0.5, 0.5), randomDouble(-0.5, 0.5), 0);
  }

  point3 defocusDiskSample() {
    auto p = randomInUnitDisk();
    return origin + defocusDiskU * p.x() + defocusDiskV * p.y();
  }

  color rayColor(const ray &r, int depth, const hittable &world) {
    if (depth <= 0) return color(0, 0, 0);
    hitRecord rec;
    if (world.hit(r, interval(0.001, INF), rec)) {
      ray scattered;
      color attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered)) {
        return attenuation * rayColor(scattered, depth - 1, world);
      }
      return color(0, 0, 0);
    }
    vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};

#endif
