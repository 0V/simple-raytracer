#ifndef RAYTRACER_MATERIALS_LDIFFUSE_LIGHTH_
#define RAYTRACER_MATERIALS_LDIFFUSE_LIGHTH_

#include "objects/hitable_base.h"
#include "textures/constant_texture.h"
#include "point_sampler_sphere.h"

class DiffuseLight : public MaterialBase
{
private:
  TexturePtr emit_;

public:
  DiffuseLight(const TexturePtr &emit) : emit_(emit) {}

  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const
  {
    return false;
  }

  virtual vec3 emitted(const Ray &r_in, const HitRecord &record, const double &u, const double &v, const vec3 &p) const
  {
    if (record.normal * r_in.direction() < 0.0)
    {
      return emit_->value(u, v, p);
    }
    else
    {
      return Vectors::Zero;
    }
  }
};
#endif // RAYTRACER_MATERIALS_LDIFFUSE_LIGHTH_