#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <numbers>
#include <random>

// Common type aliases for better code readability
using std::make_shared;
using std::shared_ptr;

// Constants used throughout the ray tracer
const double INF = std::numeric_limits<double>::infinity();  // Infinity value
const double PI = std::numbers::pi;                          // Pi constant

/**
 * Convert from degrees to radians
 * 
 * @param d Angle in degrees
 * @return Equivalent angle in radians
 */
inline double degreesToRadians(double d) { return d * PI / 180.0; }

/**
 * Generate a random double in the range [0,1)
 * Uses the Mersenne Twister engine for high-quality random numbers
 * 
 * @return Random double between 0 and 1
 */
inline double randomDouble() {
  // Static to ensure initialization happens only once for better performance
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator(std::random_device{}());
  return distribution(generator);
}

/**
 * Generate a random double in the range [min,max)
 * 
 * @param min Lower bound (inclusive)
 * @param max Upper bound (exclusive)
 * @return Random double between min and max
 */
inline double randomDouble(double min, double max) {
  return min + (max - min) * randomDouble();
}

// Include dependent headers after utility functions are defined
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif