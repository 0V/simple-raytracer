#ifndef RAYTRACER_AABB_H_
#define RAYTRACER_AABB_H_

#include "vector_utility.h"
#include "ray.h"

class AABB
{
private:
  vec3 min_, max_;

public:
  AABB() {}
  AABB(const vec3 &min, const vec3 &max) : min_(min), max_(max)
  {
  }

  void set(const vec3 &min, const vec3 &max)
  {
    min_ = min;
    max_ = max;
  }

  const vec3 &min() const { return min_; }
  const vec3 &max() const { return max_; }

  bool hit(const Ray &r, double tmin, double tmax) const
  {
    vec3 o_to_min = (min_ - r.origin());
    vec3 o_to_max = (max_ - r.origin());
    vec3 direction = r.direction();

    for (int i = 0; i < 3; i++)
    {
      double invD = 1.0 / direction[i];
      double t0 = o_to_min[i] * invD;
      double t1 = o_to_max[i] * invD;

      if (invD < 0)
      {
        std::swap(t0, t1);
      }

      tmin = t0 > tmin ? t0 : tmin;
      tmax = t1 < tmax ? t1 : tmax;

      if (tmax <= tmin)
      {
        return false;
      }
    }

    return true;
  }
};

inline AABB surrounding_box(const AABB &box0, const AABB &box1)
{
  vec3 small(std::min(box0.min().x, box1.min().x), std::min(box0.min().y, box1.min().y), std::min(box0.min().z, box1.min().z));
  vec3 big(std::max(box0.max().x, box1.max().x), std::max(box0.max().y, box1.max().y), std::max(box0.max().z, box1.max().z));
  return AABB(small, big);
}

#endif // RAYTRACER_AABB_H_