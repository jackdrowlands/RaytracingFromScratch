#include <iostream>

#include "../include/color.h"
#include "../include/ray.h"
#include "../include/vec3.h"

bool hitSphere(const point3& center, double radius, const ray& r) {
  vec3 oc = r.origin() - center;
  auto a = dot(r.direction(), r.direction());
  auto b = 2.0 * dot(oc, r.direction());
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  return discriminant > 0;
}

color rayColor(const ray& r) {
  vec3 unitDirection = unitVector(r.direction());
  auto t = 0.5 * (unitDirection.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
  constexpr auto aspectRatio = 16.0 / 9.0;
  int imageWidth = 400;

  int imageHeight = std::max(static_cast<int>(imageWidth / aspectRatio), 1);

  auto focalLength = 1.0;
  auto viewportHeight = 2.0;
  auto viewportWidth =
      viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
  auto origin = point3(0, 0, 0);

  auto viewportU = vec3(viewportWidth, 0, 0);
  auto viewportV = vec3(0, -viewportHeight, 0);

  auto pixedlDeltaU = viewportU / imageWidth;
  auto pixedlDeltaV = viewportV / imageHeight;

  auto viewportUpperLeft =
      origin - vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
  auto pixel100Loc =
      viewportUpperLeft + 0.5 * pixedlDeltaU + 0.5 * pixedlDeltaV;

  std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

  for (int i = 0; i < imageHeight; i++) {
    std::clog << "\rScanlines remaining: " << (imageHeight - i) << " "
              << std::flush;
    for (int j = 0; j < imageWidth; j++) {
      auto pixelCenter = pixel100Loc + (i * pixedlDeltaU) + (j * pixedlDeltaV);
      auto rayDirection = pixelCenter - origin;
      ray r(origin, rayDirection);

      color pixelColor = rayColor(r);
      writeColor(std::cout, pixelColor);
    }
  }

  std::clog << "\rDone" << std::endl;
}