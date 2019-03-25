#ifndef RAYTRACER_OBJECTS_FLIP_NORMALS_H_
#define RAYTRACER_OBJECTS_FLIP_NORMALS_H_

#include "vector_utility.h"
#include "objects/hitable_base.h"

class FlipNormals : public HitableBase
{
private:
  HitablePtr ptr_;

public:
  FlipNormals(const HitablePtr &ptr) : ptr_(ptr){};

  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
  {
    if (ptr_->hit(r, t_min, t_max, dist))
    {
      dist.normal = -dist.normal;
      return true;
    }
    else
    {
      return false;
    }
  }
  virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
  {
    return ptr_->bounding_box(t0, t1, box);
  }
};
#endif // RAYTRACER_OBJECTS_FLIP_NORMALS_H_