#ifndef RAYTRACER_TEXTURES_PERLIN_NOISE_TESTURE_H_
#define RAYTRACER_TEXTURES_PERLIN_NOISE_TESTURE_H_

#include "perlin_noise.h"
#include "texture_base.h"
#include "vector_utility.h"

class PerlinNoiseTexture : public TextureBase
{
private:
  PerlinNoise noise_;

public:
  PerlinNoiseTexture(double scale_ = 1) : scale(scale_) {}

  double scale;

  virtual vec3 value(const double &u, const double &v, const vec3 &p) const
  {
    return Vectors::One * noise_.at(scale * p);
  }
};
#endif // RAYTRACER_TEXTURES_PERLIN_NOISE_TESTURE_H_