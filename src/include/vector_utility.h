#ifndef RAYTRACER_VECTOR_UTILITY_H_
#define RAYTRACER_VECTOR_UTILITY_H_
#include <iostream>
#include "vector3d.h"
#include "quaternion.h"

using vec3 = Vector3d<double>;
using quat = Quaternion<double>;

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

quat QuaternionFromEular(double yaw, double pitch, double roll)
{
  // Abbreviations for the various angular functions
  double cy = cos(yaw * 0.5);
  double sy = sin(yaw * 0.5);
  double cp = cos(pitch * 0.5);
  double sp = sin(pitch * 0.5);
  double cr = cos(roll * 0.5);
  double sr = sin(roll * 0.5);

  quat q(cy * cp * cr + sy * sp * sr,
         cy * cp * sr - sy * sp * cr,
         sy * cp * sr + cy * sp * cr,
         sy * cp * cr - cy * sp * sr);

  return q;
}

quat QuaternionFromEular(const vec3 &eular)
{
  return QuaternionFromEular(eular[0], eular[1], eular[2]);
}

struct Vectors
{
  static const vec3 Zero;
  static const vec3 One;
  static const vec3 Up;
  static const vec3 Right;
  static const vec3 Back;
  static const vec3 X;
  static const vec3 Y;
  static const vec3 Z;
  static const vec3 Infinity;
  static const vec3 NegativeInfinity;
};

const vec3 Vectors::Zero = vec3(0, 0, 0);
const vec3 Vectors::One = vec3(1, 1, 1);
const vec3 Vectors::Up = vec3(0, 1, 0);
const vec3 Vectors::Right = vec3(1, 0, 0);
const vec3 Vectors::Back = vec3(0, 0, 1);
const vec3 Vectors::X = vec3(1, 0, 0);
const vec3 Vectors::Y = vec3(0, 1, 0);
const vec3 Vectors::Z = vec3(0, 0, 1);
const vec3 Vectors::Infinity = vec3(INFINITY, INFINITY, INFINITY);
const vec3 Vectors::NegativeInfinity = vec3(-INFINITY, -INFINITY, -INFINITY);

#endif // RAYTRACER_VECTOR_UTILITY_H_
