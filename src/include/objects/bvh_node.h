#ifndef RAYTRACER_OBJECTS_BVH_NODE_H_
#define RAYTRACER_OBJECTS_BVH_NODE_H_

#include <random>
#include <vector>
#include <algorithm>
#include "value_sampler.h"
#include "hitable_base.h"
#include "aabb.h"

template <int N>
struct greater_aabb
{
  int operator()(HitablePtr &a, HitablePtr &b) const
  {
    AABB box_left, box_right;
    if (a->bounding_box(0, 0, box_left) || !b->bounding_box(0, 0, box_right))
    {
      std::cerr << "no bounding box in bvh_node constructer\n";
    }
    else if (box_left.min()[N] - box_right.min()[N] < 0)
    {
      return -1;
    }
    return 1;
  }
};

template <int N>
int box_compare(const void *a, const void *b)
{
  AABB box_left, box_right;
  HitablePtr ah = *(HitablePtr *)a;
  HitablePtr bh = *(HitablePtr *)b;

  if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
  {
    std::cerr << "no bounding box in bvh_node constructor\n";
  }
  if (box_left.min()[N] - box_right.min()[N] < 0.0)
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

class BvhNode : public HitableBase
{
private:
  ValueSampler<int> sampler_ = ValueSampler<int>(0, 2);

  mutable std::random_device seed_gen_ = std::random_device();
  mutable std::mt19937 engine_ = std::mt19937(seed_gen_());
  mutable std::uniform_int_distribution<int> dist_ = std::uniform_int_distribution<int>(0, 2);

  // using greater_aabb_x = greater_aabb<0>;
  // using greater_aabb_y = greater_aabb<1>;
  // using greater_aabb_z = greater_aabb<2>;

public:
  HitablePtr left;
  HitablePtr right;
  AABB box;

  BvhNode() {}
  BvhNode(HitablePtr *l, const int &n, const double &time0, const double &time1)
  {
    int axis = sampler_.sample();
    switch (axis)
    {
    case 0:
      qsort(l, n, sizeof(HitablePtr), box_compare<0>);
      break;
    case 1:
      qsort(l, n, sizeof(HitablePtr), box_compare<1>);
      break;
    default: // == 2
      qsort(l, n, sizeof(HitablePtr), box_compare<2>);
      break;
    }

    switch (n)
    {
    case 1:
      left = right = l[0];
      break;
    case 2:
      left = l[0];
      right = l[1];
      break;
    default:
      left = std::make_shared<BvhNode>(l, n / 2, time0, time1);
      right = std::make_shared<BvhNode>(l + n / 2, n - n / 2, time0, time1);
      break;
    }

    AABB box_left, box_right;
    if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
    {
      std::cerr << "no bounding box in bvh_node constructer\n";
    }

    box = surrounding_box(box_left, box_right);
  }

  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
  {
    if (box.hit(r, t_min, t_max))
    {
      HitRecord left_rec, right_rec;
      bool hit_left = left->hit(r, t_min, t_max, left_rec);
      bool hit_right = right->hit(r, t_min, t_max, right_rec);

      if (hit_left && hit_right)
      {
        dist = left_rec.t < right_rec.t ? left_rec : right_rec;
      }
      else if (hit_left)
      {
        dist = left_rec;
      }
      else if (hit_right)
      {
        dist = right_rec;
      }
      else
      {
        return false;
      }

      return true;
    }
    else
    {
      return false;
    }
  }

  virtual bool bounding_box(const double &t0, const double &t1, AABB &b) const
  {
    b = box;

    return true;
  }
};


class BvhNodErr : public HitableBase
{
private:
  ValueSampler<int> sampler_ = ValueSampler<int>(0, 2);

  mutable std::random_device seed_gen_ = std::random_device();
  mutable std::mt19937 engine_ = std::mt19937(seed_gen_());
  mutable std::uniform_int_distribution<int> dist_ = std::uniform_int_distribution<int>(0, 2);

  using greater_aabb_x = greater_aabb<0>;
  using greater_aabb_y = greater_aabb<1>;
  using greater_aabb_z = greater_aabb<2>;

public:
  HitablePtr left;
  HitablePtr right;
  AABB box;

  BvhNode() {}
  BvhNode(const std::vector<HitablePtr> &l, const int &start, const int &n, const double &time0, const double &time1)
  {
    int axis = sampler_.sample();

    switch (axis)
    {
    case 0:
      std::sort((l.begin() + start), (l.begin() + start + n), greater_aabb_x());
      break;
    case 1:
      std::sort((l.begin() + start), (l.begin() + start + n), greater_aabb_y());
      break;
    default: // == 2
      std::sort((l.begin() + start), (l.begin() + start + n), greater_aabb_z());
      break;
    }

    switch (n)
    {
    case 1:
      left = right = l[0];
    case 2:
      left = l[0];
      right = l[1];
      break;
    default:
      left = std::make_shared<BvhNode>(l, start, n * 0.5, time0, time1);
      right = std::make_shared<BvhNode>(l, start + (n * 0.5), (1 - n) * 0.5, time0, time1);
      break;
    }

    AABB box_left, box_right;
    if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
    {
      std::cerr << "no bounding box in bvh_node constructer\n";
    }

    box = surrounding_box(box_left, box_right);
  }

  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
  {
    if (box.hit(r, t_min, t_max))
    {
      HitRecord left_rec, right_rec;
      bool hit_left = left->hit(r, t_min, t_max, left_rec);
      bool hit_right = right->hit(r, t_min, t_max, right_rec);

      if (hit_left && hit_right)
      {
        dist = left_rec.t < right_rec.t ? left_rec : right_rec;
      }
      else if (hit_left)
      {
        dist = left_rec;
      }
      else if (hit_right)
      {
        dist = right_rec;
      }
      else
      {
        return false;
      }

      return true;
    }
    else
    {
      return false;
    }
  }

  virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
  {

    return true;
  }
};

#endif // RAYTRACER_OBJECTS_BVH_NODE_H_