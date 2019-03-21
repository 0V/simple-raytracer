#ifndef RAYTRACER_OBJECT_HITABLE_H_
#define RAYTRACER_OBJECT_HITABLE_H_

#include "ray.h"

struct HitRecord
{
  double t;
  vec3 p;
  vec3 normal;
};

class IHitable
{
public:
  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const = 0;
};

#endif // RAYTRACER_OBJECT_HITABLE_H_