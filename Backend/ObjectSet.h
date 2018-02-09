#ifndef OBJECTSET
#define OBJECTSET

#include "Object.h"

class ObjectSet : public Object{
  public:
    int size;
    Object** set;

    ObjectSet() {}
    ObjectSet(Object **s, int n) { set = s; size = n; }
    virtual bool Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const;
};

bool ObjectSet::Intersect(const Ray& r, float minT, float maxT, IntersectInfo& info) const {
  IntersectInfo tempInfo;
  bool result = false;
  float closestT = maxT;
  for(int i=0; i < size; i++){
    if (set[i]->Intersect(r, minT, closestT, tempInfo)) {
      result = true;
      closestT = tempInfo.t;
      info = tempInfo;
    }
  }
  return result;
}

#endif