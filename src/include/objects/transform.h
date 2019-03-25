#ifndef RAYTEACER_OBJECTS_TRANSFORM_H_
#define RAYTEACER_OBJECTS_TRANSFORM_H_

#include "vector_utility.h"
#include "quaternion.h"
#include "hitable_base.h"

struct Transform
{

  template <int N>
  class Rotate;

  using RotateX = Rotate<0>;
  using RotateY = Rotate<1>;
  using RotateZ = Rotate<2>;

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

  template <int AxisIndex>
  class Rotate : public HitableBase
  {
  private:
    HitablePtr ptr_;
    double sin_theta_;
    double cos_theta_;
    bool has_box_;
    AABB bbox_;

    static constexpr int get_axis_a()
    {
      if constexpr (AxisIndex == 0) // X
      {
        return 1;
      }
      else // Y, Z
      {
        return 0;
      }
    }

    static constexpr int get_axis_b()
    {
      if constexpr (AxisIndex == 0) // X
      {
        return 2;
      }
      else if constexpr (AxisIndex == 1) // Y
      {
        return 2;
      }
      else // Z
      {
        return 1;
      }
    }

    vec3 rotate(const vec3 &v) const
    {
      vec3 tmp;
      tmp[AxisIndex] = v[AxisIndex];
      tmp[get_axis_a()] = cos_theta_ * v[get_axis_a()] + sin_theta_ * v[get_axis_b()];
      tmp[get_axis_b()] = -sin_theta_ * v[get_axis_a()] + cos_theta_ * v[get_axis_b()];
      return tmp;
    }

    vec3 rotate_inv(const vec3 &v) const
    {
      vec3 tmp;
      tmp[AxisIndex] = v[AxisIndex];
      tmp[get_axis_a()] = cos_theta_ * v[get_axis_a()] - sin_theta_ * v[get_axis_b()];
      tmp[get_axis_b()] = sin_theta_ * v[get_axis_a()] + cos_theta_ * v[get_axis_b()];
      return tmp;
    }

  public:
    Rotate(const HitablePtr &p, const double &angle) : ptr_(p)
    {
      double radians = RadUnit * angle;
      sin_theta_ = std::sin(radians);
      cos_theta_ = std::cos(radians);
      has_box_ = ptr_->bounding_box(0, 1, bbox_);
      vec3 min = Vectors::Infinity;
      vec3 max = Vectors::NegativeInfinity;
      for (int i = 0; i < 2; i++)
      {
        for (int j = 0; j < 2; j++)
        {
          for (int k = 0; k < 2; k++)
          {
            vec3 tmp(
                i * bbox_.max().x + (1 - i) * bbox_.min().x,
                j * bbox_.max().y + (1 - j) * bbox_.min().y,
                k * bbox_.max().z + (1 - k) * bbox_.min().z);

            vec3 tester = rotate(tmp);

            // double a = cos_theta_ * tmp[get_axis_a()] + sin_theta_ * tmp[get_axis_b()];
            // double b = -sin_theta_ * tmp[get_axis_a()] + cos_theta_ * tmp[get_axis_b()];

            // tester[AxisIndex] = tmp[AxisIndex];
            // tester[get_axis_a()] = a;
            // tester[get_axis_b()] = b;

            for (int c = 0; c < 3; c++)
            {
              if (tester[c] > max[c])
              {
                max[c] = tester[c];
              }
              if (tester[c] < min[c])
              {
                min[c] = tester[c];
              }
            }
          }
        }
      }
      bbox_ = AABB(min, max);
    }

    virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
    {
      vec3 origin = rotate_inv(r.origin());
      vec3 direction = rotate_inv(r.direction());

      Ray rotated_r(origin, direction, r.time());

      if (ptr_->hit(rotated_r, t_min, t_max, dist))
      {
        dist.p = rotate(dist.p);
        dist.normal = rotate(dist.normal);

        // direction[get_axis_a()] = cos_theta_ * direction_raw[get_axis_a()] - sin_theta_ * direction_raw[get_axis_b()];
        // direction[get_axis_b()] = -sin_theta_ * direction_raw[get_axis_a()] + cos_theta_ * direction_raw[get_axis_b()];
        return true;
      }
      else
      {
        return false;
      }
    }

    virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
    {
      box = bbox_;
      return has_box_;
    }

    static HitablePtr create(const HitablePtr &p, const double &angle)
    {
      return std::move(std::make_shared<Rotate>(p, angle));
    }
  };

  class RotateQuat : public HitableBase
  {
  private:
    HitablePtr ptr_;
    quat offset_;
    quat offset_inv_;

  public:
    RotateQuat(const HitablePtr &p, const quat &q) : ptr_(p), offset_(q), offset_inv_(offset_inv_.inverse())
    {
    }

    virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
    {
      Ray moved_r(offset_ * r.origin(), r.direction(), r.time());

      if (ptr_->hit(moved_r, t_min, t_max, dist))
      {
        dist.p = offset_inv_ * dist.p;
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
        box = AABB(offset_inv_ * box.min(), offset_inv_ * box.max());
        return true;
      }
      else
      {
        return false;
      }
    }

    static HitablePtr create(const HitablePtr &p, const quat &offset)
    {
      return std::move(std::make_shared<RotateQuat>(p, offset));
    }
  };
};
#endif // RAYTEACER_OBJECTS_TRANSFORM_H_