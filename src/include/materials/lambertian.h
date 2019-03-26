#ifndef RAYTRACER_MATERIALS_LAMBERTIAN_H_
#define RAYTRACER_MATERIALS_LAMBERTIAN_H_

#include "objects/hitable_base.h"
#include "textures/constant_texture.h"
#include "point_sampler_sphere.h"

class Lambertian : public MaterialBase
{
private:
  PointSamplerUnitSphere sampler;

public:
  TexturePtr albedo;

  Lambertian() {}
  Lambertian(const TexturePtr &albedo_) : albedo(albedo_) {}
  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const
  {
    vec3 target = record.normal + sampler.sample();
    scattered = Ray(record.p, target, r_in.time());
    attenuation = albedo->value(record.u, record.v, record.p);
    return true;
  }
};
#endif // RAYTRACER_MATERIALS_LAMBERTIAN_H_