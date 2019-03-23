#ifndef RAYTRACER_TEXTURES_TEXTURE_BASE_H_
#define RAYTRACER_TEXTURES_TEXTURE_BASE_H_

#include <memory>
#include "ray.h"
#include "materials/material_base.h"

class TextureBase;
using TexturePtr = std::shared_ptr<TextureBase>;

class TextureBase
{
public:
  virtual vec3 value(const double &u, const double &v, const vec3 &p) const = 0;
};

#endif // RAYTRACER_TEXTURES_TEXTURE_BASE_H_