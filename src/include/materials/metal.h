#ifndef RAYTRACER_MATERIALS_METAL_H_
#define RAYTRACER_MATERIALS_METAL_H_

#include "vector_utility.h"
#include "materials/material_base.h"
#include "objects/hitable_base.h"
#include "point_sampler_sphere.h"

class Metal : public MaterialBase
{
private:
  PointSamplerUnitSphere sampler;

public:
  vec3 albedo;
  double fuzz;

  Metal() {}
  Metal(vec3 albedo_, double fuzz_ = 0) : albedo(albedo_), fuzz(fuzz_) {}

  virtual bool scatter(const Ray &r_in, const HitRecord &record, ScatteredRecord &dist) const
  {
    vec3 reflected = reflect(r_in.direction(), record.normal).normalize();
    dist.specular_ray = Ray(record.p, reflected + (fuzz * sampler.sample()));
    dist.attenuation = albedo;
    dist.is_specular = true;
    return true;
  }
};

#endif // RAYTRACER_MATERIALS_METAL_H_