#ifndef RAY_H
#define RAY_H

#include "utils.h"

/**
 * Ray class representing a ray with an origin point and direction vector
 * Used as the fundamental operation in ray tracing: cast rays and see what they hit
 */
class ray {
 private:
  point3 orig;  // Origin point of the ray
  vec3 dir;     // Direction vector of the ray (not necessarily normalized)

 public:
  // Default constructor
  ray() {}

  // Constructor with origin and direction
  ray(const point3& origin, const vec3& direction)
      : orig(origin), dir(direction) {}

  // Accessor methods
  const point3& origin() const { return orig; }    // Get ray origin
  const vec3& direction() const { return dir; }    // Get ray direction

  /**
   * Calculate position along the ray at parameter t
   * Using the formula P(t) = origin + t*direction
   */
  point3 at(double t) const { return orig + t * dir; }
};

#endif