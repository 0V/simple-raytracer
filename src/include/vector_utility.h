#ifndef RAYTRACER_VECTOR_UTILITY_H_
#define RAYTRACER_VECTOR_UTILITY_H_
#include <iostream>
#include "vector3d.h"

using vec3 = Vector3d<double>;

template <typename Char, typename T>
inline std::basic_ostream<Char> &operator<<(std::basic_ostream<Char> &os, const Vector3d<T> &v)
{
  return os << Char('(') << v.x << Char(',') << v.y << Char(',') << v.z << Char(')');
}

inline vec3 reflect(const vec3 &v_in, const vec3 &n)
{
  return v_in - (2 * (v_in * n)) * n;
}

inline bool refract(const vec3 &v_in, const vec3 &n, const float &ni_over_nt, vec3 &refracted)
{
  vec3 v_in_unit = v_in.normalize();
  double vn = v_in_unit * n;
  double sin_in_pow = 1 - vn * vn;
  double discriminat = 1 - ni_over_nt * ni_over_nt * sin_in_pow;
  if (discriminat > 0)
  {
    refracted = (v_in_unit - (n * v_in_unit) * n) - n * std::sqrt(discriminat);
    return true;
  }
  else
  {
    return false;
  }
}

#endif // RAYTRACER_VECTOR_UTILITY_H_
