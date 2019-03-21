#ifndef RAYTRACER_OBJECT_HITABLE_H_
#define RAYTRACER_OBJECT_HITABLE_H_

#include <memory>
#include "ray.h"
#include "materials/material_base.h"

class HitableBase;
using HitablePtr = std::shared_ptr<HitableBase>;

struct HitRecord
{
  double t;
  vec3 p;
  vec3 normal;
  MaterialPtr mat_ptr;
};

class HitableBase
{
public:
  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const = 0;
};

#endif // RAYTRACER_OBJECT_HITABLE_H_