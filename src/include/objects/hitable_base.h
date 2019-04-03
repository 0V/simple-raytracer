#ifndef RAYTRACER_OBJECT_HITABLE_H_
#define RAYTRACER_OBJECT_HITABLE_H_

#include <memory>
#include "ray.h"
#include "aabb.h"
#include "materials/material_base.h"

class HitableBase;
using HitablePtr = std::shared_ptr<HitableBase>;

struct HitRecord
{
  float t;
  float u;
  float v;
  vec3 p;
  vec3 normal;
  MaterialPtr mat_ptr;
};

class HitableBase
{
public:
  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const = 0;
  virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const = 0;
  virtual double pdf_value(const vec3 &o, const vec3 &v) const
  {
    return 0;
  }
  virtual vec3 random(const vec3 &o) const
  {
    return Vectors::X;
  }
};

#endif // RAYTRACER_OBJECT_HITABLE_H_