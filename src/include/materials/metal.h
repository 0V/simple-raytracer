#ifndef RAYTRACER_MATERIALS_METAL_H_
#define RAYTRACER_MATERIALS_METAL_H_

#include "vector_utility.h"
#include "objects/hitable_base.h"

class Metal : public MaterialBase
{
private:
  PointSamplerSphere sampler;

public:
  vec3 albedo;
  double fuzz;

  Metal() {}
  Metal(vec3 albedo_, double fuzz_ = 0) : albedo(albedo_), fuzz(fuzz_) {}

  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const
  {
    vec3 reflected = reflect(r_in.direction(), record.normal).normalize();
    scattered = Ray(record.p, reflected + (fuzz * sampler.sample()));
    attenuation = albedo;
    return (scattered.direction() * record.normal) > 0;
  }
};

#endif // RAYTRACER_MATERIALS_METAL_H_