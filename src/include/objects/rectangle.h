#ifndef RAYTRACER_OBJECTS_RECTANGLE_XY_H_
#define RAYTRACER_OBJECTS_RECTANGLE_XY_H_

#include "vector_utility.h"
#include "objects/hitable_base.h"

constexpr double RectangleHalfThickness = 0.0001;

// class RectangleXY : public HitableBase
// {
//   MaterialPtr mat_ptr_;

// public:
//   double x0, x1, y0, y1, k;
//   double range_x_inv, range_y_inv;

//   RectangleXY() {}
//   RectangleXY(const double &x0_, const double &x1_,
//               const double &y0_, const double &y1_, const double &k_,
//               const MaterialPtr &mat_ptr)
//       : mat_ptr_(mat_ptr), x0(x0_), x1(x1_), y0(y0_), y1(y1_), k(k_), range_x_inv(1.0 / (x1 - x0)), range_y_inv(1.0 / (y1 - y0)) {}

//   // HitRecord will be changed
//   virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
//   {
//     vec3 rd = r.direction();
//     double t = (k - r.origin().z) / rd.z;
//     if (t < t_min || t > t_max)
//     {
//       return false;
//     }

//     double x = r.origin().x + t * rd.x;
//     double y = r.origin().y + t * rd.y;

//     if (x < x0 || x1 < x || y < y0 || y1 < y)
//     {
//       return false;
//     }

//     dist.normal = Vectors::Z;
//     dist.u = (x - x0) * range_x_inv;
//     dist.v = (y - y0) * range_y_inv;
//     dist.t = t;
//     dist.p = r.point_at_parameter(t);
//     dist.mat_ptr = mat_ptr_;
//     return true;
//   }

//   virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
//   {
//     box = AABB(vec3(x0, y0, k - RectangleHalfThickness), vec3(x1, y1, k + RectangleHalfThickness));
//     return true;
//   }
// };

template <int N, int M>
class Rectangle : public HitableBase
{
  MaterialPtr mat_ptr_;

public:
  double a0, a1, b0, b1, k;
  double range_a_inv, range_b_inv;

  Rectangle() {}
  Rectangle(const double &a0_, const double &a1_,
            const double &b0_, const double &b1_, const double &k_,
            const MaterialPtr &mat_ptr)
      : mat_ptr_(mat_ptr), a0(a0_), a1(a1_), b0(b0_), b1(b1_), k(k_), range_a_inv(1.0 / (a1 - a0)), range_b_inv(1.0 / (b1 - b0)) {}

  // HitRecord will be changed
  virtual bool hit(const Ray &r, const double &t_min, const double &t_max, HitRecord &dist) const
  {
    vec3 rd = r.direction();
    double t = (k - r.origin()[get_axis_index()]) / rd[get_axis_index()];
    if (t < t_min || t > t_max)
    {
      return false;
    }

    double a = r.origin()[N] + t * rd[N];
    double b = r.origin()[M] + t * rd[M];

    if (a < a0 || a1 < a || b < b0 || b1 < b)
    {
      return false;
    }

    dist.normal = get_axis();
    dist.u = (a - a0) * range_a_inv;
    dist.v = (b - b0) * range_b_inv;
    dist.t = t;
    dist.p = r.point_at_parameter(t);
    dist.mat_ptr = mat_ptr_;
    return true;
  }

  virtual bool bounding_box(const double &t0, const double &t1, AABB &box) const
  {
    box = AABB(vec3(a0, b0, k - RectangleHalfThickness), vec3(a1, b1, k + RectangleHalfThickness));
    return true;
  }

  constexpr vec3 get_axis() const
  {
    constexpr int idx = get_axis_index();
    if constexpr (idx == 0)
    {
      return Vectors::X;
    }
    else if constexpr (idx == 1)
    {
      return Vectors::Y;
    }
    else
    {
      return Vectors::Z;
    }
  }

  static constexpr int get_axis_index()
  {
    if constexpr (N == 0)
    {
      if constexpr (M == 1)
      {
        return 2;
      }
      else
      {
        return 1;
      }
    }
    else if constexpr (N == 1)
    {
      if constexpr (M == 0)
      {
        return 2;
      }
      else
      {
        return 0;
      }
    }
    else // (N == 2)
    {
      if constexpr (M == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
  }
};

using RectangleXY = Rectangle<0, 1>;
using RectangleYZ = Rectangle<1, 2>;
using RectangleZX = Rectangle<2, 0>;
using RectangleXZ = Rectangle<0, 2>;

#endif // RAYTRACER_OBJECTS_RECTANGLE_XY_H_