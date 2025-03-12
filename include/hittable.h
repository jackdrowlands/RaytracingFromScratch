#ifndef HITTABLE_H
#define HITTABLE_H

#include "utils.h"

// Forward declaration to avoid circular dependency
class material;

/**
 * Structure to record information about a ray-object intersection
 * Stores hit point, normal, material, and other intersection details
 */
class hitRecord {
 public:
  point3 p;                    // Intersection point
  vec3 normal;                 // Surface normal at intersection point
  shared_ptr<material> mat;    // Material of the hit object
  double t;                    // Ray parameter at intersection
  bool frontFace;              // Whether the ray hit the front face or back face

  /**
   * Set the face normal based on the ray direction and outward normal
   * Ensures normal always points against the ray direction
   * 
   * @param r The ray that hit the surface
   * @param outwardNormal The normal pointing outward from the surface geometry
   */
  void setFaceNormal(const ray& r, const vec3& outwardNormal) {
    // Ray hits from outside if ray direction and outward normal point in opposite directions
    frontFace = dot(r.direction(), outwardNormal) < 0;
    
    // Ensure normal always points against the incident ray
    normal = frontFace ? outwardNormal : -outwardNormal;
  }
};

/**
 * Abstract base class for objects that can be hit by a ray
 * Defines the interface for ray intersection with scene objects
 */
class hittable {
 public:
  virtual ~hittable() = default;

  /**
   * Determine if a ray intersects with this object
   * 
   * @param r The ray to test
   * @param rayT Interval of valid ray parameters to consider
   * @param rec Record to store hit information if intersection occurs
   * @return true if the ray hits the object, false otherwise
   */
  virtual bool hit(const ray& r, interval rayT, hitRecord& rec) const = 0;
};

#endif