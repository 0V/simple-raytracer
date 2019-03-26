#ifndef RAYTRACER_OBJECTS_BOX_H_
#define RAYTRACER_OBJECTS_BOX_H_

#include <array>
#include "vector_utility.h"
#include "materials/materials.h"
#include "objects/objects.h"
#include "textures/constant_texture.h"
#include "hitable_base.h"

class Box : public HitableBase
{
private:
  std::shared_ptr<HitableList> list_;
  MaterialPtr mat_ptr_;

public:
  vec3 pmin, pmax;

  Box(const vec3 &_pmin, const vec3 &_pmax, const MaterialPtr &mat_ptr) : mat_ptr_(mat_ptr), pmin(_pmin), pmax(_pmax)
  {
    std::vector<HitablePtr> list(6);
    list[0] = std::make_shared<RectangleXY>(pmin.x, pmax.x, pmin.y, pmax.y, pmax.z, mat_ptr_);
    list[1] = std::make_shared<FlipNormals>(std::make_shared<RectangleXY>(pmin.x, pmax.x, pmin.y, pmax.y, pmin.z, mat_ptr_));

    list[2] = std::make_shared<RectangleXZ>(pmin.x, pmax.x, pmin.z, pmax.z, pmax.y, mat_ptr_);
    list[3] = std::make_shared<FlipNormals>(std::make_shared<RectangleXZ>(pmin.x, pmax.x, pmin.z, pmax.z, pmin.y, mat_ptr_));

    list[4] = std::make_shared<RectangleYZ>(pmin.y, pmax.y, pmin.z, pmax.z, pmax.x, mat_ptr_);
    list[5] = std::make_shared<FlipNormals>(std::make_shared<RectangleYZ>(pmin.y, pmax.y, pmin.z, pmax.z, pmin.x, mat_ptr_));
    list_ = std::make_shared<HitableList>(list);
  }

  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
  {
    return list_->hit(r, t_min, t_max, dist);
  }

  virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
  {
    box = AABB(pmin, pmax);
    return true;
  }
};

#endif // RAYTRACER_OBJECTS_BOX_H_