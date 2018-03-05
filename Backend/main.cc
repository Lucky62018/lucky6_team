#include <iostream>
#include <fstream>
#include "float.h"
#include "ObjectSet.h"
#include "Sphere.h"
#include "Camera.h"

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
  int nx = 200;
  int ny = 100;
  int ns = 100;
  ofstream outfile("test.ppm");
  outfile << "P3\n" << nx << " " << ny << "\n255\n";

  Object* arr[2];
  arr[0] = new Sphere(Vector3D(0,0,-1), 0.5);
  arr[1] = new Sphere(Vector3D(0,-100.5,-1), 100);
  Object *set = new ObjectSet(arr, 2);

  Camera cam;

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      Vector3D col = Vector3D(0, 0, 0);
      for (int s=0; s < ns; s++) {
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        Ray r = cam.getRay(u, v);
        Vector3D p = r.TerminalWithArgument(2.0);
        col += color(r, set);
      }
      col /= float(ns);
      int ir = int(255.99*col.x);
      int ig = int(255.99*col.y);
      int ib = int(255.99*col.z);
      outfile << ir << " " << ig << " " << ib << "\n";
    }
  }
  outfile.close();
}