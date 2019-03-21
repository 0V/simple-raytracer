#ifndef RAYTRACER_VECTOR_UTILITY_H_
#define RAYTRACER_VECTOR_UTILITY_H_
#include <iostream>
#include "vector3d.h"

using vec3 = Vector3d<double>;

template <typename Char, typename T>
inline std::basic_ostream<Char> &operator<<(std::basic_ostream<Char> &os, const Vector3d<T> &v)
{
  return os << Char('(') << v.getX() << Char(',') << v.getY() << Char(',') << v.getZ() << Char(')');
}

#endif // RAYTRACER_VECTOR_UTILITY_H_
