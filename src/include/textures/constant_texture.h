#ifndef RAYTRACER_TEXTURES_CONSTANT_TEXTURES_H_
#define RAYTRACER_TEXTURES_CONSTANT_TEXTURES_H_

#include "texture_base.h"
#include "ray.h"

class ConstantTexture : public TextureBase
{
private:
  vec3 color_;

public:
  ConstantTexture() {}
  ConstantTexture(const vec3 &color) : color_(color) {}

  virtual vec3 value(const double &u, const double &v, const vec3 &p) const
  {
    return color_;
  }
};
#endif // RAYTRACER_TEXTURES_CONSTANT_TEXTURES_H_