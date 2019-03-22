#ifndef RAYTRACER_MATERIALS_DIELECTRIC_H_
#define RAYTRACER_MATERIALS_DIELECTRIC_H_

#include "vector_utility.h"
#include "objects/hitable_base.h"

class Dilectric : public MaterialBase
{
private:
public:
  // refractive index of object (n_obj / n_space) 
  double ref_idx;

  Dilectric(double ref_idx_) : ref_idx(ref_idx_) {}

  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const
  {
    attenuation = vec3(1, 1, 1);
    double ni_over_nt;
    vec3 refracted;
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), record.normal);
    if (reflected * record.normal > 0) // object to space
    {
      ni_over_nt = ref_idx; // n_obj / n_space
      outward_normal = -record.normal;
    }
    else // space to object
    {
      ni_over_nt = ref_idx; //  n_space / n_obj
      outward_normal = record.normal;
    }

    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
    {
      scattered = Ray(record.p, refracted);
      return true;
    }
    else
    {
      scattered = Ray(record.p, reflected);
      return false;
    }
  }
};

#endif // RAYTRACER_MATERIALS_DIELECTRIC_H_