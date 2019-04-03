#ifndef RAYTRACER_ONB_H_
#define RAYTRACER_ONB_H_

#include "vector_utility.h"

class Onb
{
private:
  vec3 axis_[3];

public:
  Onb() {}
  Onb(const vec3 &normal)
  {
    build_from_w(normal);
  }

  inline vec3 operator[](const int &i) const { return axis_[i]; }
  vec3 u() const { return axis_[0]; }
  vec3 v() const { return axis_[1]; }
  vec3 w() const { return axis_[2]; }
  vec3 local(const double &a, const double &b, const double &c) const
  {
    return a * u() + b * v() + c * w();
  }

  vec3 local(const vec3 &a) const
  {
    return a.x * u() + a.y * v() + a.z * w();
  }

  void build_from_w(const vec3 &normal)
  {
    axis_[2] = normal.normalize();
    vec3 a;
    if (std::fabs(w().x) > 0.9)
    {
      a = Vectors::Y;
    }
    else
    {
      a = Vectors::X;
    }
    axis_[1] = axis_[2].cross(a).normalize();
    axis_[0] = axis_[2].cross(axis_[1]).normalize();
  }
};

#endif // RAYTRACER_ONB_H_