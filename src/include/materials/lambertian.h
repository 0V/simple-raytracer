#ifndef RAYTRACER_MATERIALS_LAMBERTIAN_H_
#define RAYTRACER_MATERIALS_LAMBERTIAN_H_

#include "objects/hitable_base.h"
#include "point_sampler_sphere.h"

class Lambertian : public MaterialBase
{
private:
  PointSamplerSphere sampler;

public:
  vec3 albedo;

  Lambertian() {}
  Lambertian(vec3 albedo_) : albedo(albedo_) {}
  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const
  {
    vec3 target = record.normal + sampler.sample();
    scattered = Ray(record.p, target);
    attenuation = albedo;
    return true;
  }
};
#endif // RAYTRACER_MATERIALS_LAMBERTIAN_H_