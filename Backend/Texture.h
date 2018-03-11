#ifndef TEXTURE
#define TEXTURE

class Texture {
  public:
    virtual Vector3D GetColor(float u, float v, const Vector3D& p) const = 0;
};

class PureColorTexture : public Texture {
  public:
    Vector3D color;

    PureColorTexture(Vector3D c) : color(c) {}
    virtual Vector3D GetColor(float u, float v, const Vector3D& p) const {
      return color;
    }
};

class CheckerTexture : public Texture {
  public:
    Texture *t1;
    Texture *t2;

    CheckerTexture(Texture *a, Texture *b) : t1(a), t2(b) {}
    virtual Vector3D GetColor(float u, float v, const Vector3D& p) const {
      float k = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
      if(k < 0) {
        return t1->GetColor(u, v, p);
      } else {
        return t2->GetColor(u, v, p);
      }
    }
};

#endif