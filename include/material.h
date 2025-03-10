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
    auto scatterDir = rec.normal + randomUnitVec3();

    if (scatterDir.nearZero()) {
      scatterDir = rec.normal;
    }

    scattered = ray(rec.p, scatterDir);
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
    auto scatterDir =
        reflect(rIn.direction(), rec.normal) + fuzz * randomUnitVec3();
    scattered = ray(rec.p, scatterDir);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

 private:
  color albedo;
  double fuzz;
};

class dielectric : public material {
 public:
  dielectric(double ir) : indexOfRefraction(ir) {}

  bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation,
               ray& scattered) const override {
    attenuation = color(1.0, 1.0, 1.0);
    double ri = rec.frontFace ? (1.0/indexOfRefraction) : indexOfRefraction;

    vec3 unitDir = unitVector(rIn.direction());
    double cosTheta = std::fmin(dot(-unitDir, rec.normal), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);
    
    bool cannotRefract = ri * sinTheta > 1.0;
    vec3 dir;
    if (cannotRefract || reflectance(cosTheta, ri) > randomDouble()) {
      dir = reflect(unitDir, rec.normal);
    } else {
      dir = refract(unitDir, rec.normal, ri);
    }
    scattered = ray(rec.p, dir);
    return true;
  }

 private:
  double indexOfRefraction;

  static double reflectance(double cosine, double refIdx) {
    auto r0 = (1 - refIdx) / (1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
  }
};

#endif