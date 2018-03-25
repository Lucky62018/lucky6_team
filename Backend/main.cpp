#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include "float.h"
#include "ObjectSet.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Rectangle.h"
#include "library/json.hpp"

using namespace std;
using json = nlohmann::json;
#define NUM_THREADS 10

Vector3D color(const Ray& r, Object *s, int depth) {
  IntersectInfo info;
  if (s->Intersect(r, 0.001 , MAXFLOAT, info)) {
    Ray scattered ;
    Vector3D attenuation;
    Vector3D emitted = info.materialPointer->Emitted(info.pointOfIntersection);
    if (depth < 50 && info.materialPointer->Scatter(r, info, attenuation, scattered)) {
      return emitted + attenuation * color(scattered, s, depth + 1);
    } else {
      return emitted;
    }
  } else {
    return Vector3D(0, 0, 0);
  }
}

// ObjectSet* randomSet() {
//     int n = 500;
//     Object **list = new Object*[n+1];
//     Texture *checker = new CheckerTexture(new PureColorTexture(Vector3D(0.2, 0.3, 0.1)), new PureColorTexture(Vector3D(0.9, 0.9, 0.9)));
//     list[0] =  new Sphere(Vector3D(0,-1000,0), 1000, new Diffuse(checker));
//     int i = 1;
//     // for (int a = -11; a < 11; a++) {
//     //   for (int b = -11; b < 11; b++) {
//     //     float choose_mat = drand48();
//     //     Vector3D center(a+0.9*drand48(),0.2,b+0.9*drand48()); 
//     //     if ((center-Vector3D(4,0.2,0)).Length() > 0.9) { 
//     //       if (choose_mat < 0.8) {  // diffuse
//     //         list[i++] = new Sphere(center, 0.2, new Diffuse(Vector3D(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
//     //       }
//     //       else if (choose_mat < 0.95) { // metal
//     //         list[i++] = new Sphere(center, 0.2, new Metal(Vector3D(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48()))));
//     //       }
//     //       else {  // glass
//     //         list[i++] = new Sphere(center, 0.2, new Glass(1.5));
//     //       }
//     //     }
//     //   }
//     // }
//     Texture *marble = new MarbleTexture(100);
//     list[i++] = new Sphere(Vector3D(0, 1, 0), 1.0, new Diffuse(marble));
//     // list[i++] = new Sphere(Vector3D(0, 1, 0), 1.0, new Glass(1.5));
//     Texture *pure = new PureColorTexture(Vector3D(0.4, 0.2, 0.1));
//     list[i++] = new Sphere(Vector3D(-4, 1, 0), 1.0, new Diffuse(pure));
//     list[i++] = new Sphere(Vector3D(4, 1, 0), 1.0, new Metal(Vector3D(0.7, 0.6, 0.5)));

//     return new ObjectSet(list,i);
// }

// Object* simpleLight() {
//   Object **list = new Object*[6];
//   Texture *checker = new CheckerTexture(new PureColorTexture(Vector3D(0.2, 0.3, 0.1)), new PureColorTexture(Vector3D(0.9, 0.9, 0.9)));
//   list[0] =  new PlaneXZ(-500, 500, -500, 500, 0, new Diffuse(new PureColorTexture(Vector3D(0.25, 0.25, 0.25))));
//   list[1] = new Sphere(Vector3D(0, 1, 0), 1, new Diffuse(new MarbleTexture(100)));
//   list[2] = new Sphere(Vector3D(0, 7, 0), 2, new Light(new PureColorTexture(Vector3D(9, 9, 9))));
//   list[3] = new Rectangle(Vector3D(1.3, 0, 0.5), Vector3D(2.5, 1.6, 2.3), new Diffuse(new PureColorTexture(Vector3D(0.8, 0.6, 0.7))));
//   list[4] = new Sphere(Vector3D(-4, 1, 0), 1.0, new Glass(1.55));
//   list[5] = new Sphere(Vector3D(4, 1, 0), 1.0, new Metal(Vector3D(0.7, 0.6, 0.5)));
//   return new ObjectSet(list, 6);
// }

Object* generateObjectSet(const json& j) {
  const int n = j["objects"].size();
  Object **result = new Object*[n+1];
  // cout << j["objects"][0]["type"] << endl;
  for(int i = 0; i < n; i++) {
    // Sphere
    if(j["objects"][i]["type"] == "sphere") {
      Vector3D center(j["objects"][i]["center"]["x"], j["objects"][i]["center"]["y"], j["objects"][i]["center"]["z"]);
      float radius = j["objects"][i]["radius"];
      Material *mp = nullptr;
      if(j["objects"][i]["material"]["type"] == "marble"){
        mp = new Diffuse(new MarbleTexture(100));
      }
      if(j["objects"][i]["material"]["type"] == "glass") {
        mp = new Glass(1.55);
      }
      if(j["objects"][i]["material"]["type"] == "metal") {
        Vector3D col(j["objects"][i]["material"]["color"]["x"], j["objects"][i]["material"]["color"]["y"], j["objects"][i]["material"]["color"]["z"]);
        mp = new Metal(Vector3D(col));
      }
      if(j["objects"][i]["material"]["type"] == "pureColor") {
        Vector3D col(j["objects"][i]["material"]["color"]["x"], j["objects"][i]["material"]["color"]["y"], j["objects"][i]["material"]["color"]["z"]);
        mp = new Diffuse(new PureColorTexture(Vector3D(col)));
      }
      if(j["objects"][i]["material"]["type"] == "checker") {
        Vector3D col1(j["objects"][i]["material"]["color1"]["x"], j["objects"][i]["material"]["color1"]["y"], j["objects"][i]["material"]["color1"]["z"]);
        Vector3D col2(j["objects"][i]["material"]["color2"]["x"], j["objects"][i]["material"]["color2"]["y"], j["objects"][i]["material"]["color2"]["z"]);
        Texture *checker = new CheckerTexture(new PureColorTexture(col1), new PureColorTexture(col2));
        mp = new Diffuse(checker);
      }
      result[i] = new Sphere(center, radius, mp);
    }

    // Rectangle
    if(j["objects"][i]["type"] == "rectangle") {
      Vector3D pos1(j["objects"][i]["position1"]["x"], j["objects"][i]["position1"]["y"], j["objects"][i]["position1"]["z"]);
      Vector3D pos2(j["objects"][i]["position2"]["x"], j["objects"][i]["position2"]["y"], j["objects"][i]["position2"]["z"]);
      Material *mp = nullptr;
      if(j["objects"][i]["material"]["type"] == "marble"){
        mp = new Diffuse(new MarbleTexture(100));
      }
      if(j["objects"][i]["material"]["type"] == "glass") {
        mp = new Glass(1.55);
      }
      if(j["objects"][i]["material"]["type"] == "metal") {
        Vector3D col(j["objects"][i]["material"]["color"]["x"], j["objects"][i]["material"]["color"]["y"], j["objects"][i]["material"]["color"]["z"]);
        mp = new Metal(Vector3D(col));
      }
      if(j["objects"][i]["material"]["type"] == "pureColor") {
        Vector3D col(j["objects"][i]["material"]["color"]["x"], j["objects"][i]["material"]["color"]["y"], j["objects"][i]["material"]["color"]["z"]);
        mp = new Diffuse(new PureColorTexture(Vector3D(col)));
      }
      if(j["objects"][i]["material"]["type"] == "checker") {
        Vector3D col1(j["objects"][i]["material"]["color1"]["x"], j["objects"][i]["material"]["color1"]["y"], j["objects"][i]["material"]["color1"]["z"]);
        Vector3D col2(j["objects"][i]["material"]["color2"]["x"], j["objects"][i]["material"]["color2"]["y"], j["objects"][i]["material"]["color2"]["z"]);
        Texture *checker = new CheckerTexture(new PureColorTexture(col1), new PureColorTexture(col2));
        mp = new Diffuse(checker);
      }
      result[i] = new Rectangle(pos1, pos2, mp);
    }

    // Light
    if(j["objects"][i]["type"] == "light") {
      Vector3D center(j["objects"][i]["center"]["x"], j["objects"][i]["center"]["y"], j["objects"][i]["center"]["z"]);
      float radius = j["objects"][i]["radius"];
      result[i] = new Sphere(center, radius, new Light(new PureColorTexture(Vector3D(9, 9, 9))));
    }
    
  }
  result[n] =  new PlaneXZ(-500, 500, -500, 500, 0, new Diffuse(new PureColorTexture(Vector3D(0.25, 0.25, 0.25))));

  return new ObjectSet(result, n+1);
}

struct thread_data{
  int id;
  int x0;
  int x1;
  int x;
  int y;
  int s;
  Object* world;
  Camera camera;
  Vector3D** v;
};

void *calculate(void *data) {
  struct thread_data *mydata;
  mydata = (struct thread_data *) data;
  
  int nx = mydata->x;
  int ny = mydata->y;
  int ns = mydata->s;

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = mydata->x0; i < mydata->x1; i++) {
      Vector3D col = Vector3D(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        Ray r = mydata->camera.getRay(u, v);
        col += color(r, mydata->world, 0);
      }
      col /= float(ns);
      col = Vector3D(sqrt(col.x), sqrt(col.y), sqrt(col.z));
      mydata->v[i][j] = col;
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  time_t start,stop;
  start = time(NULL); 

  ifstream infile; 
  infile.open(argv[1]); 
  string s;
  while(!infile.eof()){
    infile >> s;
  }
  std::stringstream ss;
  ss << s;
 
 // create JSON value and read the serialization from the stream
  json j;
  ss >> j;
  // cout << setw(2) << j << endl;

  int nx = j["image"]["x"];
  int ny = j["image"]["y"];
  int ns = j["image"]["definition"];

  Vector3D lookfrom(j["camera"]["from"]["x"], j["camera"]["from"]["y"], j["camera"]["from"]["z"]);
  Vector3D lookat(j["camera"]["at"]["x"], j["camera"]["at"]["y"], j["camera"]["at"]["z"]);
  float vfov = j["camera"]["fieldOfView"];
  Camera cam(lookfrom, lookat, Vector3D(0, 1, 0), vfov, float(nx)/float(ny));

  Object *set = generateObjectSet(j);

  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  void *status;
  struct thread_data td[NUM_THREADS];
  int rc;
  int i;
  int temp = nx / NUM_THREADS;

  // 初始化并设置线程为可连接的（joinable）
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  Vector3D **vp;
  vp = new Vector3D*[nx];
  for (int i = 0; i < nx; ++i)
  {
      vp[i] = new Vector3D[ny];
  }

  for( i=0; i < NUM_THREADS; i++ ){
    cout <<"main() : creating thread, " << i << endl;
    if(i != (NUM_THREADS - 1)) {
      td[i].x0 = i * temp;
      td[i].x1 = (i + 1) * temp;
    } else {
      td[i].x0 = i * temp;
      td[i].x1 = nx;
    }
    td[i].x = nx;
    td[i].y = ny;
    td[i].s = ns;
    td[i].world = set;
    td[i].camera = cam;
    td[i].id = i;
    td[i].v = vp;
    rc = pthread_create(&threads[i], NULL, calculate, (void *)&td[i]);
    if (rc){
        cout << "Error:unable to create thread," << rc << endl;
        exit(-1);
    }
  }

  // 删除属性，并等待其他线程
  pthread_attr_destroy(&attr);
  for( i=0; i < NUM_THREADS; i++ ){
    rc = pthread_join(threads[i], &status);
    if (rc){
        cout << "Error:unable to join," << rc << endl;
        exit(-1);
    }
    cout << "Main: completed thread id :" << i ;
    cout << "  exiting with status :" << status << endl;
  }
  cout << "Main: program exiting." << endl;

  string name = j["name"];
  string suffix = ".ppm";
  ofstream outfile(name+suffix);
  outfile << "P3\n" << nx << " " << ny << "\n255\n";

  for(int m = ny - 1; m >= 0; m--) {
    for(int n = 0; n < nx; n++){
      Vector3D col = vp[n][m];
      int ir = int(255*col.x);
      int ig = int(255*col.y);
      int ib = int(255*col.z);
      outfile << ir << " " << ig << " " << ib << "\n";
    }
  }
  
  // for (int j = ny - 1; j >= 0; j--) {
  //   for (int i = 0; i < nx; i++) {
  //     Vector3D col = Vector3D(0, 0, 0);
  //     for (int s = 0; s < ns; s++) {
  //       float u = float(i + drand48()) / float(nx);
  //       float v = float(j + drand48()) / float(ny);
  //       Ray r = cam.getRay(u, v);
  //       col += color(r, set, 0);
  //     }
  //     col /= float(ns);
  //     col = Vector3D(sqrt(col.x), sqrt(col.y), sqrt(col.z));
  //     int ir = int(255*col.x);
  //     int ig = int(255*col.y);
  //     int ib = int(255*col.z);
  //     outfile << ir << " " << ig << " " << ib << "\n";
  //   }
  // }

  outfile.close();
  stop = time(NULL);
  printf("Use Time:%ld\n",(stop-start));
}