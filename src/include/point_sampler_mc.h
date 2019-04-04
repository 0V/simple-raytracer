#ifndef RAYTRACER_POINT_SAMPLER_MC_H_
#define RAYTRACER_POINT_SAMPLER_MC_H_

#include "vector_utility.h"
#include "value_sampler.h"

class PointSamplerLambertian
{
private:
  ValueSampler<double> sampler_ = ValueSampler<double>(0, 1);

public:
  PointSamplerLambertian() {}
  vec3 sample() const
  {
    double r1 = sampler_.sample();
    double r2 = sampler_.sample();
    double phi = 2 * M_PI * r1;
    double x = std::cos(phi) * std::sqrt(r2);
    double y = std::sin(phi) * std::sqrt(r2);
    double z = std::sqrt(1 - r2);
    return vec3(x, y, z);
  }
};

class PointSamplerToSphere
{
private:
  ValueSampler<double> sampler_ = ValueSampler<double>(0, 1);

public:
  PointSamplerToSphere() {}
  vec3 sample(double radius, double distance_squared) const
  {
    double r1 = sampler_.sample();
    double r2 = sampler_.sample();
    double z = 1 + r2 * (std::sqrt(1 - radius * radius / distance_squared) - 1);
    double phi = 2 * M_PI * r1;
    double r3 = std::sqrt(1 - z * z);
    double x = std::cos(phi) * r3;
    double y = std::sin(phi) * r3;
    return vec3(x, y, z);
  }
};

#endif // RAYTRACER_POINT_SAMPLER_MC_H_
