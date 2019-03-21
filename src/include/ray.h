#ifndef RAYTRACER_RAY_H_
#define RAYTRACER_RAY_H_
#include "vector_utility.h"
class Ray
{
public:
  Ray() {}
  Ray(const vec3 &from, const vec3 &dir) : va(from), vb(dir)
  {
  }

  vec3 origin() const { return va; }
  vec3 direction() const { return vb; }
  vec3 point_at_parameter(double t) const { return va + vb * t; }

  vec3 va;
  vec3 vb;
};

#endif // RAYTRACER_RAY_H_