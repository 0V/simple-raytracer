#ifndef RAYTRACER_POINT_SAMPLER_SPHERE_H_
#define RAYTRACER_POINT_SAMPLER_SPHERE_H_

#include <random>
#include "vector_utility.h"

class PointSamplerSphere
{
private:
  static std::random_device seed_gen_;
  static std::mt19937 engine_;
  static std::uniform_real_distribution<double> dist_;

public:
  PointSamplerSphere() {}
  PointSamplerSphere(const double radius_) : radius(radius_), square_radius(radius_ * radius_) {}
  const double radius = 1;
  const double square_radius = 1;

  vec3 sample() const
  {
    vec3 p;
    do
    {
      p = vec3(radius * dist_(seed_gen_), radius * dist_(seed_gen_), radius * dist_(seed_gen_));
    } while (p.getSqrLen() >= square_radius);
    return p;
  }
};

std::random_device PointSamplerSphere::seed_gen_ = std::random_device();
std::mt19937 PointSamplerSphere::engine_ = std::mt19937(seed_gen_());
std::uniform_real_distribution<double> PointSamplerSphere::dist_ = std::uniform_real_distribution<double>(-1, 1);

#endif // RAYTRACER_POINT_SAMPLER_SPHERE_H_