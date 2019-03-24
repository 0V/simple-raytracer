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

class PerlinNoise
{
private:
  std::array<double, PerlinNoiseSize> randvalue_;
  std::array<int, PerlinNoiseSize> perm_x_;
  std::array<int, PerlinNoiseSize> perm_y_;
  std::array<int, PerlinNoiseSize> perm_z_;

  ValueSampler<double> sampler_ = ValueSampler<double>(0, 1);

  std::array<double, PerlinNoiseSize> generate_perlin() const
  {
    std::array<double, PerlinNoiseSize> result;
    for (int i = 0; i < PerlinNoiseSize; i++)
    {
      result[i] = sampler_.sample();
    }

    return std::move(result);
  }

  std::array<int, PerlinNoiseSize> generate_perlin_perm() const
  {
    std::array<int, PerlinNoiseSize> result;
    for (int i = 0; i < 256; i++)
    {
      result[i] = i;
    }
    permute(result);
    return std::move(result);
  }

  void permute(std::array<int, PerlinNoiseSize> &p) const
  {
    for (int i = p.size() - 1; i > 0; i--)
    {
      int target = (int)(sampler_.sample() * (i + 1));
      std::swap(p[i], p[target]);
    }
  }

public:
  PerlinNoise()
  {
    randvalue_ = generate_perlin();
    perm_x_ = generate_perlin_perm();
    perm_y_ = generate_perlin_perm();
    perm_z_ = generate_perlin_perm();
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
      cood[i] = cood[i] * cood[i] * (3 - 2 * cood[i]);
      idxs[i] = fl;
    }

    double c[2][2][2];

    for (int di = 0; di < 2; di++)
    {
      for (int dj = 0; dj < 2; dj++)
      {
        for (int dk = 0; dk < 2; dk++)
        {
          c[di][dj][dk] = randvalue_[perm_x_[(idxs[0] + di) & 255] ^ perm_y_[(idxs[1] + dj) & 255] ^ perm_z_[(idxs[2] + dk) & 255]];
        }
      }
    }

    return trilinear_interp(c, cood[0], cood[1], cood[2]);
  }
};

#endif // RAYTRACER_TEXTURES_PERLIN_NOISE_H_