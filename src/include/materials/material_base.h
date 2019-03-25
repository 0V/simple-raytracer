#ifndef RAYTRACER_MATERIALS_MATERIAL_BASE_H_
#define RAYTRACER_MATERIALS_MATERIAL_BASE_H_

struct HitRecord;

#include "vector_utility.h"
#include "objects/hitable_base.h"

class MaterialBase
{
public:
  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const = 0;
  virtual vec3 emitted(const double &u, const double &v, const vec3 &p) const
  {
    return Vectors::Zero;
  };
};

using MaterialPtr = std::shared_ptr<MaterialBase>;

#endif // RAYTRACER_MATERIALS_MATERIAL_BASE_H_
