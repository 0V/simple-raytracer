#ifndef RAYTRACER_OBJECTS_SPHERE_H_
#define RAYTRACER_OBJECTS_SPHERE_H_

#include <memory>
#include "hitable_base.h"
#include "materials/material_base.h"

class Sphere : public HitableBase
{
public:
  vec3 center;
  double radius;
  MaterialPtr mat_ptr;

  Sphere() {}

  Sphere(const vec3 &center_, const double &radius_, const MaterialPtr &mat_ptr_) : center(center_), radius(radius_), mat_ptr(mat_ptr_)
  {
  }

  // HitRecord will be changed
  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
  {
    vec3 o_to_center = r.origin() - center;
    // ax^2 + 2bt + c
    double a = r.direction() * r.direction();
    double b = (r.direction() * o_to_center);
    double c = o_to_center * o_to_center - radius * radius;
    double discriminant = b * b - a * c;

    if (discriminant > 0)
    {
      double ans = (-b - std::sqrt(discriminant)) / a;
      if (t_min < ans && ans < t_max)
      {
        dist.t = ans;
        dist.p = r.point_at_parameter(ans);
        dist.normal = (dist.p - center) / radius;
        dist.mat_ptr = mat_ptr;
        return true;
      }

      ans = (-b + std::sqrt(discriminant)) / a;
      if (t_min < ans && ans < t_max)
      {
        dist.t = ans;
        dist.p = r.point_at_parameter(ans);
        dist.normal = (dist.p - center) / radius;
        dist.mat_ptr = mat_ptr;
        return true;
      }
    }
    return false;
  }

  virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
  {
    box = AABB(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
    return true;
  }
};

#endif // RAYTRACER_OBJECTS_SPHERE_H_