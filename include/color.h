#ifndef COLOR_H
#define COLOR_H

#include <algorithm>

#include "utils.h"
#include "vec3.h"

using color = vec3;

void writeColor(std::ostream& out, const color& pixelColor) {
  auto r = pixelColor.x();
  auto g = pixelColor.y();
  auto b = pixelColor.z();
  int rByte = std::clamp(static_cast<int>(255.999 * r), 0, 255);
  int gByte = std::clamp(static_cast<int>(255.999 * g), 0, 255);
  int bByte = std::clamp(static_cast<int>(255.999 * b), 0, 255);

  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif