#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include <vector>

#include "hittable.h"
#include "utils.h"

class hittableList : public hittable {
 public:
  std::vector<shared_ptr<hittable>> objects;

  hittableList() {}
  hittableList(shared_ptr<hittable> obj) { add(obj); }

  void clear() { objects.clear(); }

  void add(shared_ptr<hittable> obj) { objects.push_back(obj); }

  bool hit(const ray& r, interval rayT,
           hitRecord& rec) const override {
    hitRecord tempRec;
    bool hitAnything = false;
    auto closestSoFar = rayT.max;

    for (const auto& obj : objects) {
      if (obj->hit(r, interval(rayT.min, closestSoFar), tempRec)) {
        hitAnything = true;
        closestSoFar = tempRec.t;
        rec = tempRec;
      }
    }
    return hitAnything;
  }
};

#endif