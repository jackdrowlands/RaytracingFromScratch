#ifndef COLOR_H
#define COLOR_H

#include <algorithm>

#include "utils.h"
#include "vec3.h"
#include "interval.h"

using color = vec3;

inline double linearToGamma(double linearComponent) {
  if (linearComponent > 0) return std::sqrt(linearComponent);
  return 0;
}

void writeColor(std::ostream& out, const color& pixelColor) {
  double r = linearToGamma(pixelColor.x());
  double g = linearToGamma(pixelColor.y());
  double b = linearToGamma(pixelColor.z());
  static const interval intensity(0.000, 0.999);
  int rByte = static_cast<int>(255.999 * intensity.clamp(r));
  int gByte = static_cast<int>(255.999 * intensity.clamp(g));
  int bByte = static_cast<int>(255.999 * intensity.clamp(b));

  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif