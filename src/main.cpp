#include <cassert>
#include <chrono>

#include "../include/hittable.h"
#include "../include/hittableList.h"
#include "../include/sphere.h"
#include "../include/utils.h"
#include "../include/camera.h"

int main() {
  auto totalStartTime = std::chrono::high_resolution_clock::now();
  
  hittableList world;
  world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, 0, -5), 0.5));
  world.add(make_shared<sphere>(point3(5, 0, -10), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  camera cam;
  cam.aspectRatio = 16.0 / 9.0;
  cam.imageWidth = 2560;  // Using a smaller resolution for profiling
  cam.samplesPerPixel = 10;  // Using fewer samples for profiling

  auto renderStartTime = std::chrono::high_resolution_clock::now();
  cam.render(world);
  auto renderEndTime = std::chrono::high_resolution_clock::now();
  
  auto totalEndTime = std::chrono::high_resolution_clock::now();
  
  auto renderTime = std::chrono::duration_cast<std::chrono::milliseconds>(renderEndTime - renderStartTime);
  auto totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(totalEndTime - totalStartTime);
  
  std::clog << "Render time: " << renderTime.count() << " ms" << std::endl;
  std::clog << "Total execution time: " << totalTime.count() << " ms" << std::endl;
  
  return 0;
}