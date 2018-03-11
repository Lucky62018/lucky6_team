#ifndef MATERIAL
#define MATERIAL

#include "Ray.h"
#include "Object.h"
#include "Texture.h"

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

bool refract(const Vector3D& v, const Vector3D& n, float k, Vector3D& refracted) {
  Vector3D unitV = GetUnitizedCopy(v);
  float dot = DotProduct(unitV, n);
  float i = 1 - k * k * (1 - dot * dot);
  if (i > 0) {
    refracted = k * (unitV - dot * n) - sqrt(i) * n;
    return true;
  } else return false;
}

float polynomialApproximate(float cosine, float refractIndex) {
  float k = (1 - refractIndex) / (1 + refractIndex);
  return k * k + (1 - k * k) * pow((1 - cosine), 5);
}

class Material {
  public:
    virtual bool Scatter(const Ray& comingRay, const IntersectInfo& info, Vector3D& attenuation, Ray& scattered) const = 0;
};

class Diffuse : public Material {
  public:
    Texture *ratio;

    Diffuse(Texture *r) : ratio(r) {}

    virtual bool Scatter(const Ray& comingRay, const IntersectInfo& info, Vector3D& attenuation, Ray& scattered) const {
      Vector3D target = info.pointOfIntersection + info.normal + randomPointInSphere();
      scattered = Ray(info.pointOfIntersection, target - info.pointOfIntersection);
      attenuation = ratio->GetColor(0, 0, info.pointOfIntersection);
      return true;
    }
};

class Metal : public Material {
  public:
    Vector3D ratio;

    Metal(const Vector3D& r) : ratio(r) {}
    virtual bool Scatter(const Ray& comingRay, const IntersectInfo& info, Vector3D& attenuation, Ray& scattered) const {
      Vector3D reflected = reflect(GetUnitizedCopy(comingRay.direction), info.normal);
      scattered = Ray(info.pointOfIntersection, reflected);
      attenuation = ratio;
      return (DotProduct(scattered.direction, info.normal) > 0);
    }
};

class Glass : public Material {
  public:
    float refractIndex;

    Glass(float r) : refractIndex(r) {}
    virtual bool Scatter(const Ray& comingRay, const IntersectInfo& info, Vector3D& attenuation, Ray& scattered) const {
      Vector3D outerNormal;
      Vector3D reflected = reflect(comingRay.direction, info.normal);
      float k;
      attenuation = Vector3D(1, 1, 1);
      Vector3D refracted;
      float reflectProb;
      float cosine;
      if (DotProduct(comingRay.direction, info.normal) > 0) {
        outerNormal = -info.normal;
        k = refractIndex;
        cosine = refractIndex * DotProduct(comingRay.direction, info.normal) / comingRay.direction.Length();
        // cosine = sqrt(1 - refractIndex*refractIndex*(1-cosine*cosine));
      } else {
        outerNormal = info.normal;
        k = 1 / refractIndex;
        cosine = -DotProduct(comingRay.direction, info.normal) / comingRay.direction.Length();
      }
      if (refract(comingRay.direction, outerNormal, k, refracted)) {
        reflectProb = polynomialApproximate(cosine, refractIndex);
      } else {
        scattered = Ray(info.pointOfIntersection, reflected);
        reflectProb = 1;
      }
      if(drand48() < reflectProb) scattered = Ray(info.pointOfIntersection, reflected);
      else scattered = Ray(info.pointOfIntersection, refracted);
      return true;
    }
};

#endif