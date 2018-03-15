#ifndef RECTANGLE
#define RECTANGLE

#include "Object.h"

class PlaneXY : public Object {
  public:
    float x0, x1, y0, y1, k;
    Material *mp;

    PlaneXY(float _x0, float _x1, float _y0, float _y1, float _k, Material *m) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(m) {}
    virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const {
      float t = (k - r.origin.z) / r.direction.z;
      if (t < minT || t > maxT) return false;
      float x = r.origin.x + t * r.direction.x;
      float y = r.origin.y + t * r.direction.y;
      if (x < x0 || x > x1 || y < y0 || y > y1) return false;
      info.u = (x - x0) / (x1 - x0);
      info.v = (y - y0) / (y1 - y0);
      info.t = t;
      info.materialPointer = mp;
      info.pointOfIntersection = r.TerminalWithArgument(t);
      info.normal = Vector3D(0, 0, 1);
      return true;
    }
};

class PlaneXZ : public Object {
  public:
    float x0, x1, z0, z1, k;
    Material *mp;

    PlaneXZ(float _x0, float _x1, float _z0, float _z1, float _k, Material *m) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(m) {}
    virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const {
      float t = (k - r.origin.y) / r.direction.y;
      if (t < minT || t > maxT) return false;
      float x = r.origin.x + t * r.direction.x;
      float z = r.origin.z + t * r.direction.z;
      if (x < x0 || x > x1 || z < z0 || z > z1) return false;
      info.u = (x - x0) / (x1 - x0);
      info.v = (z - z0) / (z1 - z0);
      info.t = t;
      info.materialPointer = mp;
      info.pointOfIntersection = r.TerminalWithArgument(t);
      info.normal = Vector3D(0, 0, 1);
      return true;
    }
};

class PlaneYZ : public Object {
  public:
    float y0, y1, z0, z1, k;
    Material *mp;

    PlaneYZ(float _y0, float _y1, float _z0, float _z1, float _k, Material *m) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(m) {}
    virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const {
      float t = (k - r.origin.x) / r.direction.x;
      if (t < minT || t > maxT) return false;
      float y = r.origin.y + t * r.direction.y;
      float z = r.origin.z + t * r.direction.z;
      if (y < y0 || y > y1 || z < z0 || z > z1) return false;
      info.u = (y - y0) / (y1 - y0);
      info.v = (z - z0) / (z1 - z0);
      info.t = t;
      info.materialPointer = mp;
      info.pointOfIntersection = r.TerminalWithArgument(t);
      info.normal = Vector3D(0, 0, 1);
      return true;
    }
};

class NormalFlip : public Object {
  public:
    Object *ptr;

    NormalFlip(Object *p) : ptr(p) {}
    virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const {
      if(ptr->Intersect(r, minT, maxT, info)) {
        info.normal = -info.normal;
        return true;
      } else {
        return false;
      }
    }
};

class Rectangle : public Object {
  public:
    Vector3D pmin, pmax;
    Object *listPtr;

    Rectangle(const Vector3D& p0, const Vector3D& p1, Material *mp) {
      pmin = p0;
      pmax = p1;
      Object **list = new Object*[6];
      list[0] = new PlaneXY(p0.x, p1.x, p0.y, p1.y, p1.z, mp);
      list[1] = new NormalFlip(new PlaneXY(p0.x, p1.x, p0.y, p1.y, p1.z, mp));
      list[2] = new PlaneXZ(p0.x, p1.x, p0.z, p1.z, p1.y, mp);
      list[3] = new NormalFlip(new PlaneXZ(p0.x, p1.x, p0.z, p1.z, p1.y, mp));
      list[4] = new PlaneYZ(p0.y, p1.y, p0.z, p1.z, p1.x, mp);
      list[5] = new NormalFlip(new PlaneYZ(p0.y, p1.y, p0.z, p1.z, p1.x, mp));
      listPtr = new ObjectSet(list, 6);
    }
    virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const {
      return listPtr->Intersect(r, minT, maxT, info);
    }
};

#endif 