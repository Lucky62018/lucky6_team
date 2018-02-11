#include <iostream>
#include <fstream>
#include "float.h"
#include "ObjectSet.h"
#include "Sphere.h"

using namespace std;

Vector3D color(const Ray& r, Object *s) {
  IntersectInfo info;
  if (s->Intersect(r, 0 , MAXFLOAT, info)) {
    return 0.5 * Vector3D(info.normal.x+1, info.normal.y+1, info.normal.z+1);
  } else {
    Vector3D unitDirection = GetUnitizedCopy(r.direction);
    float t = 0.5 * (unitDirection.y + 1);
    return (1-t) * Vector3D(1,1,1) + t * Vector3D(0.9, 0.7, 1);
  }
}

int main() {
  int nx = 400;
  int ny = 200;
  ofstream outfile("test.ppm");
  outfile << "P3\n" << nx << " " << ny << "\n255\n";

  Vector3D leftLowerCorner(-2, -1, -0.2);
  Vector3D horizontal(4, 0, 0);
  Vector3D vertical(0, 2, 0);
  Vector3D origin(0, 0, 0);

  Object* arr[2];
  arr[0] = new Sphere(Vector3D(-1,0,-1), 0.5);
  arr[1] = new Sphere(Vector3D(1,0,-1), 0.6);
  Object *set = new ObjectSet(arr, 2);

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);
      Ray r(origin, leftLowerCorner + u * horizontal + v * vertical);
      Vector3D col = color(r, set);
      int ir = int(255.99*col.x);
      int ig = int(255.99*col.y);
      int ib = int(255.99*col.z);
      outfile << ir << " " << ig << " " << ib << "\n";
    }
  }
  outfile.close();
}