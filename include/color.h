#ifndef COLOR_H
#define COLOR_H

#include <algorithm>

#include "utils.h"
#include "vec3.h"
#include "interval.h"

/**
 * Color type alias using vec3 to represent RGB colors
 * Components are typically in the range [0,1] where:
 * - x component represents red
 * - y component represents green
 * - z component represents blue
 */
using color = vec3;

/**
 * Convert from linear color space to gamma space
 * Uses simple gamma=2 approximation (square root)
 * This corrects for perceptual non-linearity in human vision
 *
 * @param linearComponent A single color component in linear space
 * @return The gamma-corrected color component
 */
inline double linearToGamma(double linearComponent) {
  if (linearComponent > 0) return std::sqrt(linearComponent);
  return 0;
}

/**
 * Write a color to an output stream in PPM format
 * Applies gamma correction and maps from [0,1] to [0,255]
 *
 * @param out Output stream to write to
 * @param pixelColor Color to write (in linear space)
 */
void writeColor(std::ostream& out, const color& pixelColor) {
  // Apply gamma correction (convert from linear to gamma space)
  double r = linearToGamma(pixelColor.x());
  double g = linearToGamma(pixelColor.y());
  double b = linearToGamma(pixelColor.z());
  
  // Clamp color values to [0,0.999] interval
  static const interval intensity(0.000, 0.999);
  
  // Scale to [0,255] and convert to integer
  int rByte = static_cast<int>(255.999 * intensity.clamp(r));
  int gByte = static_cast<int>(255.999 * intensity.clamp(g));
  int bByte = static_cast<int>(255.999 * intensity.clamp(b));

  // Write the color values to the output stream
  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif