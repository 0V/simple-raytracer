#ifndef RAYTRACER_OBJECTS_CONSTANT_MEDIUM_H_
#define RAYTRACER_OBJECTS_CONSTANT_MEDIUM_H_

#include "vector_utility.h"
#include "objects/hitable_base.h"
#include "materials/isotropic.h"
#include "textures/texture_base.h"
#include "value_sampler.h"

class ConstantMedium : public HitableBase
{
private:
  HitablePtr boundary_;
  double pdf_;
  MaterialPtr phase_function_;

  ValueSampler<double> sampler_ = ValueSampler<double>(0, 1);

public:
  ConstantMedium(const HitablePtr &ptr, const double &pdf, const TexturePtr &tex)
      : boundary_(ptr), pdf_(pdf), phase_function_(std::make_shared<Isotropic>(tex)) {}

  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
  {
    //    bool db = sampler_.sample();
    bool db = false;

    HitRecord rec1, rec2;

    if (boundary_->hit(r, -INFINITY, INFINITY, rec1))
    {
      if (boundary_->hit(r, rec1.t + 0.0001, INFINITY, rec2))
      {
        if (db)
        {
          std::cerr << "t1 " << rec1.t << " " << rec2.t << "\n";
        }

        if (rec1.t < t_min)
        {
          rec1.t = t_min;
        }
        if (rec2.t > t_max)
        {
          rec2.t = t_max;
        }
        if (rec1.t >= rec2.t)
        {
          return false;
        }
        if (rec1.t < 0)
        {
          rec1.t = 0;
        }

        double length = r.direction().length();

        double distance_inside_boudary = (rec2.t - rec1.t) * length;
        double hit_distance = -(1 / pdf_) * std::log(sampler_.sample());

        if (hit_distance < distance_inside_boudary)
        {
          if (db)
          {
            std::cerr << "hit_distantce = " << hit_distance << "\n";
          }
          else
          {
            dist.t = rec1.t + hit_distance / length;
          }
          if (db)
          {
            std::cerr << "dist.t = " << dist.t << "\n";
          }
          else
          {
            dist.p = r.point_at_parameter(dist.t);
          }
          if (db)
          {
            std::cerr << "dist.p = " << dist.p << "\n";
          }
          else
          {
            dist.normal = Vectors::X; // arbitary
            dist.mat_ptr = phase_function_;
            return true;
          }
        }
      }
    }
    return false;
  }

  virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
  {
    return boundary_->bounding_box(t0, t1, box);
  }
};
#endif // RAYTRACER_OBJECTS_CONSTANT_MEDIUM_H_