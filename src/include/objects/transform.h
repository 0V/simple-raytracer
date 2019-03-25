#ifndef RAYTEACER_OBJECTS_TRANSFORM_H_
#define RAYTEACER_OBJECTS_TRANSFORM_H_

#include "vector_utility.h"
#include "hitable_base.h"

struct Transform
{
  class Translate : public HitableBase
  {
  private:
    HitablePtr ptr_;
    vec3 offset_;

  public:
    Translate(const HitablePtr &p, const vec3 &offset) : ptr_(p), offset_(offset)
    {
    }

    virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
    {
      Ray moved_r(r.origin() - offset_, r.direction(), r.time());

      if (ptr_->hit(moved_r, t_min, t_max, dist))
      {
        dist.p += offset_;
        return true;
      }
      else
      {
        return false;
      }
    }

    virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
    {
      if (ptr_->bounding_box(t0, t1, box))
      {
        box = AABB(box.min() + offset_, box.max() + offset_);
        return true;
      }
      else
      {
        return false;
      }
    }

    static HitablePtr create(const HitablePtr &p, const vec3 &offset)
    {
      return std::move(std::make_shared<Translate>(p, offset));
    }
  };
};
#endif // RAYTEACER_OBJECTS_TRANSFORM_H_