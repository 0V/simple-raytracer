#ifndef RAYTRACER_OBJECTS_MOVING_SPHERE_H_
#define RAYTRACER_OBJECTS_MOVING_SPHERE_H_

#include <memory>
#include "hitable_base.h"
#include "materials/material_base.h"

class MovingSphere : public HitableBase
{
public:
  vec3 center0, center1, center_dir, center_mid;
  double time0, time1, time_range;
  double radius;
  MaterialPtr mat_ptr;

  MovingSphere() {}

  MovingSphere(const vec3 &center0_, const vec3 &center1_,
               const double &time0_, const double &time1_,
               const double &radius_, const MaterialPtr &mat_ptr_)
      : center0(center0_), center1(center1_), center_dir(center1_ - center0_), center_mid(center0_ + center_dir * 0.5),
        time0(time0_), time1(time1_), time_range(time1_ - time0_),
        radius(radius_), mat_ptr(mat_ptr_)
  {
  }

  vec3 center(const double &time) const
  {
    return center0 + ((time - time0) / time_range) * center_dir;
  }

  // HitRecord will be changed
  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
  {
    vec3 cen = center(r.time());
    vec3 o_to_center = r.origin() - cen;
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
        dist.normal = (dist.p - cen) / radius;
        dist.mat_ptr = mat_ptr;
        return true;
      }

      ans = (-b + std::sqrt(discriminant)) / a;
      if (t_min < ans && ans < t_max)
      {
        dist.t = ans;
        dist.p = r.point_at_parameter(ans);
        dist.normal = (dist.p - cen) / radius;
        dist.mat_ptr = mat_ptr;
        return true;
      }
    }
    return false;
  }

  virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
  {
    box = AABB(center_mid - vec3(radius, radius, radius), center_mid + vec3(radius, radius, radius));
    return true;
  }
};

#endif // RAYTRACER_OBJECTS_MOVING_SPHERE_H_