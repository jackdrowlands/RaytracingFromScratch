#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
 private:
  point3 center;
  double radius;

 public:
  sphere(const point3& centre, double radius)
      : center(centre), radius(std::fmax(0, radius)) {}

  bool hit(const ray& r, double rayTmin, double rayTmax,
           hitRecord& rec) const override {
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - std::pow(radius, 2);

    auto discriminant = std::pow(radius, 2) - a * c;
    if (discriminant < 0) return false;

    auto sqrtd = std::sqrt(discriminant);

    auto root = (h - sqrtd) / a;
    if (root <= rayTmin || rayTmax <= root) {
      root = (h + sqrtd) / a;
      if (root <= rayTmin || rayTmax <= root) return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outwardNormal);
    return true;
  }
};

#endif