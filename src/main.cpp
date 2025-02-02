#include "../include/hittable.h"
#include "../include/hittableList.h"
#include "../include/sphere.h"
#include "../include/utils.h"

color rayColor(const ray& r, const hittable& world) {
  hitRecord rec;
  if (world.hit(r, 0, INF, rec)) {
    return 0.5 * (rec.normal + color(1, 1, 1));
  }

  vec3 unitDirection = unitVector(r.direction());
  auto a = 0.5 * (unitDirection.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
  constexpr auto aspectRatio = 16.0 / 9.0;
  int imageWidth = 2560;

  int imageHeight = std::max(static_cast<int>(imageWidth / aspectRatio), 1);

  hittableList world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

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
      auto pixelCenter = pixel100Loc + (j * pixedlDeltaU) + (i * pixedlDeltaV);
      auto rayDirection = pixelCenter - origin;
      ray r(origin, rayDirection);

      color pixelColor = rayColor(r, world);
      writeColor(std::cout, pixelColor);
    }
  }

  std::clog << "\rDone" << std::endl;
}