#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
 public:
  virtual ~material() = default;

  virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation,
                       ray& scattered) const = 0;
};

class lambertian : public material {
 public:
  lambertian(const color& albedo) : albedo(albedo) {}

  bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation,
               ray& scattered) const override {
    auto scattereDir = rec.normal + randomUnitVec3();

    if (scattereDir.nearZero()) {
      scattereDir = rec.normal;
    }

    scattered = ray(rec.p, scattereDir);
    attenuation = albedo;
    return true;
  }

 private:
  color albedo;
};

class metal : public material {
 public:
  metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}

  bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation,
               ray& scattered) const override {
    auto scattereDir = reflect(rIn.direction(), rec.normal) + fuzz * randomUnitVec3();
    scattered = ray(rec.p, scattereDir);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

 private:
  color albedo;
  double fuzz;
};

#endif