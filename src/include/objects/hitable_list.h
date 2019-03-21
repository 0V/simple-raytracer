#ifndef RAYTRACER_OBJECTS_HITABLE_LIST_H_
#define RAYTRACER_OBJECTS_HITABLE_LIST_H_

#include <memory>
#include <vector>
#include "hitable.h"

class HitableList : public IHitable
{
public:
  std::vector<HitablePtr> list;

  HitableList() {}
  HitableList(const std::vector<HitablePtr> &l) : list(l)
  {
  }

  bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
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
};

#endif // RAYTRACER_OBJECTS_HITABLE_LIST_H_