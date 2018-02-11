#ifndef RAY
#define RAY

#include "Vector3D.h"

class Ray {
  public:
    Vector3D origin;
    Vector3D direction;

    //constructors
    Ray() {}
    Ray(const Vector3D& a, const Vector3D& b) { origin = a; direction = b;}

    Vector3D TerminalWithArgument(float k) const { return origin + k * direction; }

};

#endif