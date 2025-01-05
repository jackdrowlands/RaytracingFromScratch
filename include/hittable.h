#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hitRecord {
  point3 p;
  vec3 normal;
  double t;
};

class hittable {
  virtual ~hittable() = default;

  virtual bool hit(const ray& r, double rayTmin, double rayTmax,
                   hitRecord& rec) const = 0;
};

#endif