#ifndef VECTOR3D
#define VECTOR3D

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vector3D {
  public:
    //coordinate variables
    float x, y, z;

    //constructors
    Vector3D() {}
    Vector3D(float x, float y, float z) {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    //overload some operators for convenience of calculating vectors
    Vector3D operator-() const { return Vector3D(-x, -y, -z); }
    inline Vector3D& operator+=(const Vector3D &v);
    inline Vector3D& operator-=(const Vector3D &v);
    inline Vector3D& operator*=(const float a);
    inline Vector3D& operator/=(const float a);

    //useful vector functions
    float Length() const { return sqrt(x*x + y*y + z*z); }
    inline void Unitize(); //unitize current Vector3D obeject
};

//implementations of functions in Vector3D
inline Vector3D& Vector3D::operator+=(const Vector3D &v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D &v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

inline Vector3D& Vector3D::operator*=(const float a) {
  x *= a;
  y *= a;
  z *= a;
  return *this;
}

inline Vector3D& Vector3D::operator/=(const float a) {
  x /= a;
  y /= a;
  z /= a;
  return *this;
}

inline void Vector3D::Unitize() {
  float k = 1 / Length();
  x *= k;
  y *= k;
  z *= k;
}


//implement some global functions to overload binary operations of Vector3D
inline Vector3D operator+(const Vector3D &v1, const Vector3D &v2) {
  float x = v1.x + v2.x;
  float y = v1.y + v2.y;
  float z = v1.z + v2.z;
  return Vector3D(x,y,z);
}

inline Vector3D operator-(const Vector3D &v1, const Vector3D &v2) {
  float x = v1.x - v2.x;
  float y = v1.y - v2.y;
  float z = v1.z - v2.z;
  return Vector3D(x,y,z);
}

inline Vector3D operator*(const Vector3D &v1, const Vector3D &v2) {
  float x = v1.x * v2.x;
  float y = v1.y * v2.y;
  float z = v1.z * v2.z;
  return Vector3D(x,y,z);
}

inline Vector3D operator/(const Vector3D &v1, const Vector3D &v2) {
  float x = v1.x / v2.x;
  float y = v1.y / v2.y;
  float z = v1.z / v2.z;
  return Vector3D(x,y,z);
}

inline Vector3D operator*(float k, const Vector3D &v) {
  return Vector3D(v.x*k, v.y*k, v.z*k);
}

inline Vector3D operator/(const Vector3D &v, float k) {
  return Vector3D(v.x/k, v.y/k, v.z/k);
}

//implement dot product and cross product of Vector3D
inline float DotProduct(const Vector3D &v1, const Vector3D &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector3D CrossProduct(const Vector3D &v1, const Vector3D &v2) {
  float x = v1.y * v2.z - v1.z * v2.y;
  float y = v1.z * v2.x - v1.x * v2.z;
  float z = v1.x * v2.y - v1.y * v2.x;
  return Vector3D(x,y,z);
}

//unitize and get the copy of an Vector3D object
inline Vector3D GetUnitizedCopy(Vector3D v) {
  return v / v.Length();
}

#endif