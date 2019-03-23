#ifndef RAYTRACER_TEXTURES_CHECKER_TEXTURES_H_
#define RAYTRACER_TEXTURES_CHECKER_TEXTURES_H_

#include <cmath>
#include "texture_base.h"
#include "ray.h"

class CheckerTexture : public TextureBase
{
private:
  TexturePtr tex_even, tex_odd;

public:
  CheckerTexture() {}
  CheckerTexture(const TexturePtr &tex0, const TexturePtr &tex1) : tex_even(tex0), tex_odd(tex1) {}

  virtual vec3 value(const double &u, const double &v, const vec3 &p) const
  {
    double sines = std::sin(10 * p.x) * std::sin(10 * p.y) * std::sin(10 * p.z);
    if (sines < 0)
    {
      return tex_odd->value(u, v, p);
    }
    else
    {
      return tex_even->value(u, v, p);
    }
  }
};
#endif // RAYTRACER_TEXTURES_CHECKER_TEXTURES_H_