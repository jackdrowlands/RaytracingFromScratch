#include "../include/hittable.h"
#include "../include/hittableList.h"
#include "../include/sphere.h"
#include "../include/utils.h"
#include "../include/camera.h"

int main() {
  hittableList world;

  auto matGround = make_shared<lambertian>(color(0.8,0.8,0.0));
  auto matCenter = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto matLeft = make_shared<metal>(color(0.8, 0.8, 0.8));
  auto matRight = make_shared<metal>(color(0.8, 0.6, 0.2));

  world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, matGround));
  world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, matCenter));
  world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, matLeft));
  world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, matRight));

  camera cam;
  cam.aspectRatio = 16.0 / 9.0;
  cam.imageWidth = 2560;
  cam.samplesPerPixel = 10;
  cam.maxDepth = 10;

  cam.render(world);

  return 0;
}