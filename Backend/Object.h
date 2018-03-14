#ifndef OBJECT
#define OBJECT

#include "Ray.h"

class Material;

struct IntersectInfo {
  float t;
  Vector3D pointOfIntersection;
  Vector3D normal;
  Material *materialPointer;
  float u;
  float v;
};

class Object {
  public:
    virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const = 0;
};

#endif