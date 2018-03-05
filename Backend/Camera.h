#ifndef CAMERA
#define CAMERA

#include "Ray.h"

class Camera {
  public:
    Vector3D origin;
    Vector3D leftLowerCorner;
    Vector3D horizontal;
    Vector3D vertical;

    Camera() {
      leftLowerCorner = Vector3D(-2, -1, -1);
      horizontal = Vector3D(4, 0, 0);
      vertical = Vector3D(0, 2, 0);
      origin = Vector3D(0, 0, 0);
    }

    Ray getRay(float u, float v) {
      return Ray(origin, leftLowerCorner + u * horizontal + v * vertical - origin);
    }

};

#endif