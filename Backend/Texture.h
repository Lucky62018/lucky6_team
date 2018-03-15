#ifndef TEXTURE
#define TEXTURE

#include "library/FastNoise.h"
#include "Vector3D.h"

class Texture {
  public:
    virtual Vector3D GetColor(const Vector3D& p) const = 0;
};

class PureColorTexture : public Texture {
  public:
    Vector3D color;

    PureColorTexture(Vector3D c) : color(c) {}
    virtual Vector3D GetColor(const Vector3D& p) const {
      return color;
    }
};

class CheckerTexture : public Texture {
  public:
    Texture *t1;
    Texture *t2;

    CheckerTexture(Texture *a, Texture *b) : t1(a), t2(b) {}
    virtual Vector3D GetColor(const Vector3D& p) const {
      float k = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
      if(k < 0) {
        return t1->GetColor(p);
      } else {
        return t2->GetColor(p);
      }
    }
};

class MarbleTexture : public Texture {
  public:
    float scale;
    FastNoise noise;

    MarbleTexture(float a) : scale(a) {
      noise.SetNoiseType(FastNoise::PerlinFractal);
      noise.SetInterp(FastNoise::Linear);
      noise.SetFrequency(0.02);
      noise.SetFractalOctaves(5);
    }
    virtual Vector3D GetColor(const Vector3D& p) const {
      // return 0.5 * (1 + sin(scale * p.z + 10 * Turb(p))) * Vector3D(1, 1, 1);
      // std::cout << p.x << p.y << p.z << std::endl;
      Vector3D temp = scale * p;
      // std::cout << noise.GetNoise(temp.x, temp.y, temp.z) << std::endl;
      // return fabs(noise.GetNoise(temp.x, temp.y, temp.z)) * Vector3D(1,1,1);
      return Turb(temp) * Vector3D(1,1,1);
    }

    float Turb(const Vector3D& p, int depth=7) const {
      float accum = 0;
      Vector3D temp = p;
      float weight = 1.0;
      for(int i = 0; i < depth; i++) {
        accum += weight * noise.GetNoise(p.x, p.y, p.z);
        weight *= 0.5;
        temp *= 2;
      }
      return fabs(accum);
    }
};


#endif