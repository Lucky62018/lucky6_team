#ifndef CAMERA
#define CAMERA

#include "Ray.h"

class Camera {
  public:
    Vector3D origin;
    Vector3D leftLowerCorner;
    Vector3D horizontal;
    Vector3D vertical;

    Camera(Vector3D from, Vector3D at, Vector3D vup, float vfov, float aspect) { // vfov is top to bottom in degrees
      Vector3D u, v, w;
      float theta = vfov * M_PI / 180;
      float halfHeight = tan(theta/2);
      float halfWidth = aspect * halfHeight;
      origin = from;
      w = GetUnitizedCopy(from - at);
      u = GetUnitizedCopy(CrossProduct(vup, w));
      v = CrossProduct(w, u);
      leftLowerCorner = origin - halfWidth * u - halfHeight * v - w;
      horizontal = 2 * halfWidth * u;
      vertical = 2 * halfHeight * v;
    }

    // Camera() {
    //   leftLowerCorner = Vector3D(-2, -1, -1);
    //   horizontal = Vector3D(4, 0, 0);
    //   vertical = Vector3D(0, 2, 0);
    //   origin = Vector3D(0,0,0);
    // }


    Ray getRay(float a, float b) {
      return Ray(origin, leftLowerCorner + a * horizontal + b * vertical - origin);
    }

};

#endif