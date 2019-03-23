#ifndef RAYTRACER_OBJECTS_HITABLE_LIST_H_
#define RAYTRACER_OBJECTS_HITABLE_LIST_H_

#include <memory>
#include <vector>
#include "hitable_base.h"

class MaterialBase;

class HitableList : public HitableBase
{
public:
  std::vector<HitablePtr> list;

  HitableList() {}
  HitableList(const std::vector<HitablePtr> &l) : list(l)
  {
  }

  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
  {
    HitRecord tmp_rec;
    bool any_hit = false;
    double t_closest = t_max;
    for (auto &h : list)
    {
      if (h->hit(r, t_min, t_closest, tmp_rec))
      {
        any_hit = true;
        t_closest = tmp_rec.t;
        dist = tmp_rec;
      }
    }
    return any_hit;
  }

  virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
  {
    const int size = list.size();
    if (size < 1)
    {
      return false;
    }

    AABB tmp_box;
    if (list[0]->bounding_box(t0, t1, tmp_box))
    {
      box = tmp_box;
    }
    else
    {
      return false;
    };

    for (int i = 0; i < size; i++)
    {
      if (list[0]->bounding_box(t0, t1, tmp_box))
      {
        box = surrounding_box(box, tmp_box);
      }
      else
      {
        return false;
      }
    }

    return true;
  }
};

#endif // RAYTRACER_OBJECTS_HITABLE_LIST_H_