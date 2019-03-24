#ifndef RAYTRACER_POINT_SAMPLER_SPHERE_H_
#define RAYTRACER_POINT_SAMPLER_SPHERE_H_

#include <random>
#include "vector_utility.h"
#include "value_sampler.h"

class PointSamplerSphere
{
private:
  ValueSampler<double> sampler_ = ValueSampler<double>(-1, 1);

public:
  PointSamplerSphere() {}
  PointSamplerSphere(const double &radius_) : radius(radius_), square_radius(radius_ * radius_) {}
  const double radius = 1;
  const double square_radius = 1;

  vec3 sample() const
  {
    vec3 p;
    do
    {
      p = vec3(radius * sampler_.sample(), radius * sampler_.sample(), radius * sampler_.sample());
    } while (p.square_length() >= square_radius);
    return p;
  }
};

class PointSamplerUnitSphere
{
private:
  ValueSampler<double> sampler_ = ValueSampler<double>(-1, 1);

public:
  PointSamplerUnitSphere() {}
  vec3 sample() const
  {
    vec3 p;
    do
    {
      p = vec3(sampler_.sample(), sampler_.sample(), sampler_.sample());
    } while (p.square_length() >= 1);
    return p;
  }
};

#endif // RAYTRACER_POINT_SAMPLER_SPHERE_H_