#ifndef RAYTRACER_OBJECTS_SPHERE_H_
#define RAYTRACER_OBJECTS_SPHERE_H_

#include "hitable.h"

class Sphere : public IHitable
{
public:
  vec3 center;
  double radius;

  Sphere() {}
  Sphere(vec3 center_, double radius_) : center(center_), radius(radius_)
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
        dist.normal = (dist.p - center).getUnit();
        return true;
      }

      ans = (-b + std::sqrt(discriminant)) / a;
      if (t_min < ans && ans < t_max)
      {
        dist.t = ans;
        dist.p = r.point_at_parameter(ans);
        dist.normal = (dist.p - center).getUnit();
        return true;
      }
    }
    return false;
  }
};

#endif // RAYTRACER_OBJECTS_SPHERE_H_