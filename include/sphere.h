#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

/**
 * Sphere class representing a 3D sphere with a center, radius, and material
 * Implements the hittable interface for ray-sphere intersection
 */
class sphere : public hittable {
 private:
  point3 center;               // Center point of the sphere
  double radius;               // Radius of the sphere
  shared_ptr<material> mat;    // Material of the sphere

 public:
  /**
   * Construct a sphere with given center, radius, and material
   * Ensures radius is non-negative
   */
  sphere(const point3& centre, double radius, shared_ptr<material> mat)
      : center(centre), radius(std::fmax(0, radius)), mat(mat) {}

  /**
   * Determine if a ray intersects with the sphere
   * Uses the quadratic formula for ray-sphere intersection
   * 
   * @param r The ray to test
   * @param rayT Interval of valid ray parameters to consider
   * @param rec Record to store hit information if intersection occurs
   * @return true if the ray hits the sphere, false otherwise
   */
  bool hit(const ray& r, interval rayT,
           hitRecord& rec) const override {
    // Vector from ray origin to sphere center
    vec3 oc = center - r.origin();
    
    // Coefficients for the quadratic equation
    auto a = r.direction().lengthSquared();
    auto h = dot(r.direction(), oc);
    auto c = oc.lengthSquared() - std::pow(radius, 2);

    // Discriminant determines number of intersections
    auto discriminant = h * h - a * c;
    if (discriminant < 0) return false;  // No intersection

    // Find the nearest valid intersection
    auto sqrtd = std::sqrt(discriminant);
    
    // Try the closer intersection first
    auto root = (h - sqrtd) / a;
    if (!rayT.surrounds(root)) {
      // If closer intersection is invalid, try the farther one
      root = (h + sqrtd) / a;
      if (!rayT.surrounds(root)) return false;  // Both intersections invalid
    }

    // Record hit information
    rec.t = root;
    rec.p = r.at(rec.t);  // Compute intersection point
    
    // Normal points outward from center
    vec3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outwardNormal);
    
    rec.mat = mat;  // Set material at intersection
    return true;
  }
};

#endif