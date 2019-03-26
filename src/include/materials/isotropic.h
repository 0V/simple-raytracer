#ifndef RAYTRACER_MATERIALS_ISOTROPIC_H_
#define RAYTRACER_MATERIALS_ISOTROPIC_H_

#include "material_base.h"
#include "textures/constant_texture.h"
#include "point_sampler_sphere.h"

class Isotropic : public MaterialBase
{
private:
  TexturePtr tex_;
  PointSamplerUnitSphere sampler_;

public:
  Isotropic(const TexturePtr &tex) : tex_(tex) {}

  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const
  {
    scattered = Ray(record.p, sampler_.sample());
    attenuation = tex_->value(record.u, record.v, record.p);
    return true;
  }
};

#endif // RAYTRACER_MATERIALS_ISOTROPIC_H_