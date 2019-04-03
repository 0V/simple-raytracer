#ifndef RAYTRACER_MATERIALS_MATERIAL_BASE_H_
#define RAYTRACER_MATERIALS_MATERIAL_BASE_H_

struct HitRecord;

#include "vector_utility.h"
#include "objects/hitable_base.h"

class MaterialBase
{
public:
  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &albedo, Ray &scattered, double &pdf) const
  {
    return false;
  }

  virtual double scattering_pdf(const Ray &r_in, const HitRecord &record, const Ray &scattered) const
  {
    return false;
  }
  virtual vec3 emitted(const double &u, const double &v, const vec3 &p) const
  {
    return Vectors::Zero;
  };
};

using MaterialPtr = std::shared_ptr<MaterialBase>;

#endif // RAYTRACER_MATERIALS_MATERIAL_BASE_H_
