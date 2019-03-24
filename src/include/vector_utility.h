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

inline bool refract(const vec3 &v_in, const vec3 &n, const double &ni_over_nt, vec3 &refracted)
{
  vec3 v_in_unit = v_in.normalize();
  double vn = v_in_unit * n;
  double sin_in_pow = 1 - vn * vn;
  double discriminant = 1 - ni_over_nt * ni_over_nt * sin_in_pow;
  if (discriminant > 0)
  {
    refracted = (ni_over_nt * (v_in_unit - vn * n)) - n * std::sqrt(discriminant);
    return true;
  }
  else
  {
    return false;
  }
}

// Schlick's approximation of Fresnel factor
inline double schlick_fresnel(const double &cosine, const double &ref_idx)
{
  double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5);
}

// Schlick's approximation of Fresnel factor
inline double schlick_fresnel(const double &cosine, const double &ref_idx_in, const double &ref_idx_out)
{
  double r0 = (ref_idx_in - ref_idx_out) / (ref_idx_in + ref_idx_out);
  r0 *= r0;
  return r0 + (ref_idx_in - r0) * std::pow((1 - cosine), 5);
}

struct Vectors
{
  static const vec3 Zero;
  static const vec3 One;
  static const vec3 Up;
};

const vec3 Vectors::Zero = vec3(0, 0, 0);
const vec3 Vectors::One = vec3(1, 1, 1);
const vec3 Vectors::Up = vec3(0, 1, 0);

#endif // RAYTRACER_VECTOR_UTILITY_H_
