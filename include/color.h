#ifndef COLOR_H
#define COLOR_H

#include "utils.h"
#include "vec3.h"

using color = vec3;

void writeColor(std::ostream& out, const color& pixelColor) {
  auto r = pixelColor.x();
  auto g = pixelColor.y();
  auto b = pixelColor.z();
  int rByte = std::clamp(static_cast<int>(255.999 * r), 0, 256);
  int gByte = static_cast<int>(255.999 * g);
  int bByte = static_cast<int>(255.999 * b);

  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif