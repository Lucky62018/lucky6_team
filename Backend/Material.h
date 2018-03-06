#ifndef MATERIAL
#define MATERIAL

#include "Ray.h"
#include "Object.h"

struct IntersectInfo;

Vector3D randomPointInSphere() {
  Vector3D p;
  do {
    p = 2 * Vector3D(drand48(),drand48(),drand48()) - Vector3D(1,1,1);
  } while (p.Length() * p.Length() >= 1);
  return p;
}

Vector3D reflect(const Vector3D& v, const Vector3D& n) {
  return v - 2 * DotProduct(v, n) * n;
}

class Material {
  public:
    virtual bool Scatter(const Ray& comingRay, const IntersectInfo& info, Vector3D& attenuation, Ray& scattered) const = 0;
};

class Diffuse : public Material {
  public:
    Vector3D ratio;

    Diffuse(const Vector3D& r) : ratio(r) {}

    virtual bool Scatter(const Ray& comingRay, const IntersectInfo& info, Vector3D& attenuation, Ray& scattered) const {
      Vector3D target = info.pointOfIntersection + info.normal + randomPointInSphere();
      scattered = Ray(info.pointOfIntersection, target - info.pointOfIntersection);
      attenuation = ratio;
      return true;
    }
};

class Mental : public Material {
  public:
    Vector3D ratio;

    Mental(const Vector3D& r) : ratio(r) {}
    virtual bool Scatter(const Ray& comingRay, const IntersectInfo& info, Vector3D& attenuation, Ray& scattered) const {
      Vector3D reflected = reflect(GetUnitizedCopy(comingRay.direction), info.normal);
      scattered = Ray(info.pointOfIntersection, reflected);
      attenuation = ratio;
      return (DotProduct(scattered.direction, info.normal) > 0);
    }
};

#endif