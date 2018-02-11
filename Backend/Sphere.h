#ifndef SPHERE
#define SPHERE

#include "Object.h"

class Sphere : public Object{
  public:
    Vector3D center;
    float radius;
    
    Sphere() {}
    Sphere(Vector3D c, float r) {
      center = c;
      radius = r;
    }

    virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const;
};

bool Sphere::Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const {
  Vector3D oc = r.origin - center;
  float a = DotProduct(r.direction, r.direction);
  float b = 2 * DotProduct(oc, r.direction);
  float c = DotProduct(oc, oc) - radius * radius;
  float d = b * b - 4 * a * c;
  if (d > 0){
    float temp = (-b - sqrt(d))/(2 * a);
    if (temp < maxT && temp > minT ) {
      info.t = temp;
      info.pointOfIntersection = r.TerminalWithArgument(temp);
      info.normal = (info.pointOfIntersection - center) / radius;
      return true;
    }
    temp = (-b + sqrt(d))/(2 * a);
    if (temp < maxT && temp > minT ) {
      info.t = temp;
      info.pointOfIntersection = r.TerminalWithArgument(temp);
      info.normal = (info.pointOfIntersection - center) / radius;
      return true;
    }
  }
  return false;
}

#endif