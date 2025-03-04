#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <numbers>
#include <random>

using std::make_shared;
using std::shared_ptr;

const double INF = std::numeric_limits<double>::infinity();
const double PI = std::numbers::pi;

inline double degreesToRadians(double d) { return d * PI / 180.0; }

// returns random real in [0,1)
inline double randomDouble() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

// returns random real in [min, max)
inline double randomDouble(double min, double max) {
  return min + (max - min) * randomDouble();
}

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif