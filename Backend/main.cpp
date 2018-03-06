#include <iostream>
#include <fstream>
#include "float.h"
#include "ObjectSet.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

using namespace std;

Vector3D color(const Ray& r, Object *s, int depth) {
  IntersectInfo info;
  if (s->Intersect(r, 0.001 , MAXFLOAT, info)) {
    Ray scattered ;
    Vector3D attenuation;
    if (depth < 50 && info.materialPointer->Scatter(r, info, attenuation, scattered)) {
      return attenuation * color(scattered, s, depth + 1);
    } else {
      return Vector3D(0, 0, 0);
    }
  } else {
    Vector3D unitDirection = GetUnitizedCopy(r.direction);
    float t = 0.5 * (unitDirection.y + 1);
    return (1-t) * Vector3D(1,1,1) + t * Vector3D(0.5, 0.7, 1);
  }
}

int main() {
  int nx = 200;
  int ny = 100;
  int ns = 100;
  ofstream outfile("test.ppm");
  outfile << "P3\n" << nx << " " << ny << "\n255\n";

  Object* arr[4];
  arr[0] = new Sphere(Vector3D(0,0,-1), 0.5, new Diffuse(Vector3D(0.8, 0.3, 0.3)));
  arr[1] = new Sphere(Vector3D(0,-100.5,-1), 100, new Diffuse(Vector3D(0.8, 0.8, 0)));
  arr[2] = new Sphere(Vector3D(1,0,-1), 0.5, new Mental(Vector3D(0.8, 0.6, 0.2)));
  arr[3] = new Sphere(Vector3D(-1,0,-1), 0.5, new Mental(Vector3D(0.8, 0.8, 0.8)));
  Object *set = new ObjectSet(arr, 4);


  Camera cam;

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      Vector3D col = Vector3D(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        Ray r = cam.getRay(u, v);
        Vector3D p = r.TerminalWithArgument(2.0);
        col += color(r, set, 0);
      }
      col /= float(ns);
      col = Vector3D(sqrt(col.x), sqrt(col.y), sqrt(col.z));
      int ir = int(255.99*col.x);
      int ig = int(255.99*col.y);
      int ib = int(255.99*col.z);
      outfile << ir << " " << ig << " " << ib << "\n";
    }
  }
  outfile.close();
}