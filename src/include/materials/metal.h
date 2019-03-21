#ifndef RAYTRACER_MATERIALS_METAL_H_
#define RAYTRACER_MATERIALS_METAL_H_

#include "vector_utility.h"
#include "objects/hitable_base.h"

class Metal : public MaterialBase
{
public:
  vec3 albedo;

  Metal() {}
  Metal(vec3 albedo_) : albedo(albedo_) {}

  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const
  {
    vec3 reflected = reflect(r_in.direction(), record.normal).getUnit();
    scattered = Ray(record.p, reflected);
    attenuation = albedo;
    return (scattered.direction() * record.normal) > 0;
  }
};

#endif // RAYTRACER_MATERIALS_METAL_H_