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

#endif // RAYTRACER_VECTOR_UTILITY_H_
