#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

/**
 * Abstract base class for all materials
 * Defines how light interacts with surfaces
 */
class material {
 public:
  virtual ~material() = default;

  /**
   * Determine how a ray scatters when hitting a surface with this material
   * 
   * @param rIn Incident ray that hit the surface
   * @param rec Hit record containing information about the intersection
   * @param attenuation How much the light is attenuated by this scatter
   * @param scattered The resulting scattered ray
   * @return true if the ray is scattered, false if absorbed
   */
  virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation,
                       ray& scattered) const = 0;
};

/**
 * Lambertian (diffuse) material that scatters light randomly
 * Simulates matte surfaces like chalk or unfinished wood
 */
class lambertian : public material {
 public:
  /**
   * Construct a lambertian material with given albedo (color reflectance)
   */
  lambertian(const color& albedo) : albedo(albedo) {}

  /**
   * Scatter incoming ray with diffuse (lambertian) reflection
   * Rays are scattered in random directions with cosine-weighted distribution
   */
  bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation,
               ray& scattered) const override {
    // Generate a random scatter direction
    auto scatterDir = rec.normal + randomUnitVec3();

    // Catch degenerate scatter direction (when random vector is opposite to normal)
    if (scatterDir.nearZero()) {
      scatterDir = rec.normal;
    }

    // Create scattered ray
    scattered = ray(rec.p, scatterDir);
    
    // Set attenuation based on material color
    attenuation = albedo;
    
    // Lambertian always scatters (never absorbs completely)
    return true;
  }

 private:
  color albedo;  // Surface color/reflectance
};

/**
 * Metal material that reflects light according to law of reflection
 * Simulates polished metal surfaces with optional fuzziness
 */
class metal : public material {
 public:
  /**
   * Construct a metal material
   * 
   * @param albedo Surface color/reflectance
   * @param fuzz Amount of reflection fuzziness (0=perfect mirror, higher=more fuzzy)
   */
  metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}

  /**
   * Scatter incoming ray with metallic reflection
   * Rays are reflected with some randomness based on fuzziness
   */
  bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation,
               ray& scattered) const override {
    // Calculate reflection direction with added fuzziness
    auto scatterDir =
        reflect(rIn.direction(), rec.normal) + fuzz * randomUnitVec3();
    
    // Create scattered ray
    scattered = ray(rec.p, scatterDir);
    
    // Set attenuation based on material color
    attenuation = albedo;
    
    // Only scatter if the ray reflects outward (not into the surface)
    return (dot(scattered.direction(), rec.normal) > 0);
  }

 private:
  color albedo;  // Surface color/reflectance
  double fuzz;   // Reflection fuzziness factor
};

/**
 * Dielectric material that both reflects and refracts light
 * Simulates transparent materials like glass, water, or diamonds
 */
class dielectric : public material {
 public:
  /**
   * Construct a dielectric material
   * 
   * @param ir Index of refraction (air=1.0, glass≈1.5, diamond≈2.4)
   */
  dielectric(double ir) : indexOfRefraction(ir) {}

  /**
   * Scatter incoming ray with reflection or refraction
   * Uses Snell's Law and Fresnel equations to determine behavior
   */
  bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation,
               ray& scattered) const override {
    // Dielectrics don't absorb light (clear glass/water)
    attenuation = color(1.0, 1.0, 1.0);
    
    // Determine relative index of refraction based on which side we're hitting
    double ri = rec.frontFace ? (1.0/indexOfRefraction) : indexOfRefraction;

    // Get unit direction vector of incoming ray
    vec3 unitDir = unitVector(rIn.direction());
    
    // Calculate cosine and sine of incidence angle
    double cosTheta = std::fmin(dot(-unitDir, rec.normal), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta*cosTheta);
    
    // Determine if we can refract based on Snell's Law
    bool cannotRefract = ri * sinTheta > 1.0;  // Total internal reflection case
    
    vec3 dir;
    // Decide whether to reflect or refract
    if (cannotRefract || reflectance(cosTheta, ri) > randomDouble()) {
      // Reflect
      dir = reflect(unitDir, rec.normal);
    } else {
      // Refract
      dir = refract(unitDir, rec.normal, ri);
    }
    
    // Create scattered ray
    scattered = ray(rec.p, dir);
    
    // Dielectrics always scatter (reflection or refraction)
    return true;
  }

 private:
  double indexOfRefraction;  // Index of refraction of the material

  /**
   * Calculate reflectance using Schlick's approximation for Fresnel equations
   * Determines what fraction of light is reflected vs refracted
   */
  static double reflectance(double cosine, double refIdx) {
    // Schlick's approximation
    auto r0 = (1 - refIdx) / (1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
  }
};

#endif