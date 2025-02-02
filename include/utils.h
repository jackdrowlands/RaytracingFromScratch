#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double INF = std::numeric_limits<double>::infinity();
const double PI = std::numbers::pi;

inline double degreesToRadians(double d) { return d * PI / 180.0; }

#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif