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
    return noise_.at(scale * p) * Vectors::One;
  }
};

class PerlinNoiseTurbTexture : public TextureBase
{
private:
  PerlinNoise noise_;

public:
  PerlinNoiseTurbTexture(double scale_ = 1) : scale(scale_) {}

  double scale;

  virtual vec3 value(const double &u, const double &v, const vec3 &p) const
  {
    return noise_.at_turb(scale * p) * Vectors::One;
  }
};

class PerlinNoiseTurbStraightTexture : public TextureBase
{
private:
  PerlinNoise noise_;

public:
  PerlinNoiseTurbStraightTexture(double scale_ = 1) : scale(scale_) {}

  double scale;

  virtual vec3 value(const double &u, const double &v, const vec3 &p) const
  {
    return 0.5 * (1 + noise_.at_turb(scale * p)) * Vectors::One;
  }
};

class PerlinNoiseMarbleTexture : public TextureBase
{
private:
  PerlinNoise noise_;

public:
  PerlinNoiseMarbleTexture(double scale_ = 1) : scale(scale_) {}

  double scale;

  virtual vec3 value(const double &u, const double &v, const vec3 &p) const
  {
    return 0.5 * (1 + std::sin(scale * p.z + 10 *noise_.at_turb(scale * p))) * Vectors::One;
  }
};

#endif // RAYTRACER_TEXTURES_PERLIN_NOISE_TESTURE_H_