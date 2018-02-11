#ifndef OBJECT
#define OBJECT

#include "Ray.h"

struct IntersectInfo {
  float t;
  Vector3D pointOfIntersection;
  Vector3D normal;
};

class Object {
  public:
    virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const = 0;
};

#endif