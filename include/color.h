#ifndef COLOR_H
#define COLOR_H

#include <algorithm>

#include "utils.h"
#include "vec3.h"
#include "interval.h"

using color = vec3;

void writeColor(std::ostream& out, const color& pixelColor) {
  auto r = pixelColor.x();
  auto g = pixelColor.y();
  auto b = pixelColor.z();
  static const interval intensity(0.000, 0.999);
  int rByte = static_cast<int>(255.999 * intensity.clamp(r));
  int gByte = static_cast<int>(255.999 * intensity.clamp(g));
  int bByte = static_cast<int>(255.999 * intensity.clamp(b));

  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif