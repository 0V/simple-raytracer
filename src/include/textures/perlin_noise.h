#ifndef RAYTRACER_TEXTURES_PERLIN_NOISE_H_
#define RAYTRACER_TEXTURES_PERLIN_NOISE_H_

#include <array>
#include "vector_utility.h"
#include "value_sampler.h"

constexpr int PerlinNoiseSize = 256;

inline double trilinear_interp(const double c[2][2][2], const double &u, const double &v, const double &w)
{
  double accum = 0;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      for (int k = 0; k < 2; k++)
      {
        accum += (i * u + (1 - i) * (1 - u)) *
                 (j * v + (1 - j) * (1 - v)) *
                 (k * w + (1 - k) * (1 - w)) * c[i][j][k];
      }
    }
  }
  return accum;
}
inline double perlin_interp(const vec3 c[2][2][2], const std::array<double, 3> &cood)
{
  std::array<double, 3> cc;
  for (int i = 0; i < 3; i++)
  {
    cc[i] = cood[i] * cood[i] * (3 - 2 * cood[i]);
  }

  double accum = 0;

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      for (int k = 0; k < 2; k++)
      {
        vec3 weight_v(cood[0] - i, cood[1] - j, cood[2] - k);
        accum += (i * cc[0] + (1 - i) * (1 - cc[0])) *
                 (j * cc[1] + (1 - j) * (1 - cc[1])) *
                 (k * cc[2] + (1 - k) * (1 - cc[2])) *
                 (c[i][j][k] * weight_v);
      }
    }
  }
  return accum;
}

inline float perlin_interp(vec3 c[2][2][2], float u, float v, float w)
{
  float uu = u * u * (3 - 2 * u);
  float vv = v * v * (3 - 2 * v);
  float ww = w * w * (3 - 2 * w);
  float accum = 0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++)
      {
        vec3 weight_v(u - i, v - j, w - k);
        accum += (i * uu + (1 - i) * (1 - uu)) *
                 (j * vv + (1 - j) * (1 - vv)) *
                 (k * ww + (1 - k) * (1 - ww)) * (c[i][j][k] * weight_v);
      }
  return accum;
}

class PerlinNoise
{
private:
  std::array<vec3, PerlinNoiseSize> randvec_;
  std::array<int, PerlinNoiseSize> perm_x_;
  std::array<int, PerlinNoiseSize> perm_y_;
  std::array<int, PerlinNoiseSize> perm_z_;

  ValueSampler<double> sampler_ = ValueSampler<double>(0, 1);
  ValueSampler<double> sampler_11_ = ValueSampler<double>(-1, 1);

  void permute(std::array<int, PerlinNoiseSize> &p) const
  {
    for (int i = p.size() - 1; i > 0; i--)
    {
      int target = (int)(sampler_.sample() * (i + 1));
      std::swap(p[i], p[target]);
    }
  }

  void generate_perlin()
  {
    for (int i = 0; i < PerlinNoiseSize; i++)
    {
      randvec_[i] = vec3(sampler_11_.sample(), sampler_11_.sample(), sampler_11_.sample()).normalize();
    }
  }

  void generate_perlin_perm()
  {
    for (int i = 0; i < PerlinNoiseSize; i++)
    {
      perm_x_[i] = perm_y_[i] = perm_z_[i] = i;
    }
    permute(perm_x_);
    permute(perm_y_);
    permute(perm_z_);
  }

public:
  PerlinNoise()
  {
    generate_perlin();
    generate_perlin_perm();
  }

  double at(const vec3 &p) const
  {
    constexpr int Dimention = 3;
    std::array<double, Dimention> cood;
    std::array<int, Dimention> idxs;
    for (int i = 0; i < Dimention; i++)
    {
      double fl = std::floor(p[i]);
      cood[i] = p[i] - fl;
      // cood[i] = cood[i] * cood[i] * (3 - 2 * cood[i]);
      idxs[i] = fl;
    }

    vec3 c[2][2][2];

    for (int di = 0; di < 2; di++)
    {
      for (int dj = 0; dj < 2; dj++)
      {
        for (int dk = 0; dk < 2; dk++)
        {
          c[di][dj][dk] = randvec_[perm_x_[(idxs[0] + di) & 255] ^ perm_y_[(idxs[1] + dj) & 255] ^ perm_z_[(idxs[2] + dk) & 255]];
        }
      }
    }

    return perlin_interp(c, cood);
    //    return perlin_interp(c, cood[0], cood[1], cood[2]);
  }
};

#endif // RAYTRACER_TEXTURES_PERLIN_NOISE_H_