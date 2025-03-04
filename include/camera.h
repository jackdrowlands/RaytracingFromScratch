#ifndef CAMERA_H
#define CAMERA_H

#include <chrono>
#include "hittable.h"

class camera {
 public:
  double aspectRatio = 16.0 / 9.0;
  int imageWidth = 2560;
  int samplesPerPixel = 10;

  void render(const hittable &world) {
    initialize();

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    for (int i = 0; i < imageHeight; i++) {
      std::clog << "\rScanlines remaining: " << (imageHeight - i) << " "
                << std::flush;
      for (int j = 0; j < imageWidth; j++) {
        color pixelColor = color(0, 0, 0);
        for (int s = 0; s < samplesPerPixel; s++) {
          ray r = getRay(i, j);
          pixelColor += rayColor(r, world);
        }
        writeColor(std::cout, pixelColor * pixelSamplesScale);
      }
    }
    std::clog << "\rDone" << std::endl;
  }

 private:
  int imageHeight;            // Rendered image height
  point3 origin;              // Camera origin
  point3 pixel00Loc;          // Location of pixel 0, 0
  vec3 pixelDeltaU;           // Offset to pixel to the right
  vec3 pixelDeltaV;           // Offset to pixel below
  double pixelSamplesScale;   // Average number of samples per pixel

  void initialize() {
    imageHeight = std::max(static_cast<int>(imageWidth / aspectRatio), 1);

    pixelSamplesScale = 1.0 / samplesPerPixel;

    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth =
        viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
    origin = point3(0, 0, 0);

    auto viewportU = vec3(viewportWidth, 0, 0);
    auto viewportV = vec3(0, -viewportHeight, 0);

    pixelDeltaU = viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight;

    auto viewportUpperLeft =
        origin - vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    pixel00Loc =
        viewportUpperLeft + 0.5 * pixelDeltaU + 0.5 * pixelDeltaV;
  }

  ray getRay(int i, int j) {
    auto offset = sampleSquare();
    auto pixelSample = pixel00Loc + (j + offset.x()) * pixelDeltaU +
        (i + offset.y()) * pixelDeltaV;
    return ray(origin, pixelSample - origin);
  }

  vec3 sampleSquare() {
    return vec3(randomDouble(-0.5,0.5), randomDouble(-0.5,0.5), 0);
  }

  color rayColor(const ray &r, const hittable &world) {
    hitRecord rec;
    if (world.hit(r, interval(0, INF), rec)) {
      vec3 direction = randomOnHemisphere(rec.normal);
      return 0.5 * rayColor(ray(rec.p, direction), world);
    }
    vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};

#endif