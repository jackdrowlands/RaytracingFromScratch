#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include <vector>

#include "hittable.h"
#include "utils.h"

/**
 * Container class for multiple hittable objects
 * Implements the hittable interface to allow ray intersection with a collection of objects
 */
class hittableList : public hittable {
 public:
  // Collection of objects in the scene
  std::vector<shared_ptr<hittable>> objects;

  // Constructors
  hittableList() {}  // Empty list
  hittableList(shared_ptr<hittable> obj) { add(obj); }  // List with a single object

  // Clear all objects from the list
  void clear() { objects.clear(); }

  // Add an object to the list
  void add(shared_ptr<hittable> obj) { objects.push_back(obj); }

  /**
   * Determine if a ray hits any object in the list
   * If multiple objects are hit, returns the closest hit to the ray origin
   * 
   * @param r The ray to test
   * @param rayT Interval of valid ray parameters to consider
   * @param rec Record to store hit information for the closest hit
   * @return true if any object is hit, false otherwise
   */
  bool hit(const ray& r, interval rayT,
           hitRecord& rec) const override {
    hitRecord tempRec;
    bool hitAnything = false;
    auto closestSoFar = rayT.max;  // Track distance to closest hit so far

    // Check each object for intersection
    for (const auto& obj : objects) {
      // Only consider hits closer than the closest hit so far
      if (obj->hit(r, interval(rayT.min, closestSoFar), tempRec)) {
        hitAnything = true;
        closestSoFar = tempRec.t;  // Update closest hit distance
        rec = tempRec;             // Save this hit as the current best
      }
    }
    
    return hitAnything;
  }
};

#endif