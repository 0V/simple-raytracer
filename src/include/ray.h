#ifndef RAYTRACER_RAY_H_
#define RAYTRACER_RAY_H_
#include "vector_utility.h"
class Ray
{

  vec3 origin_;
  vec3 direction_;
  double time_;

public:
  Ray() {}
  Ray(const vec3 &from, const vec3 &dir, const double &ti = 0.0) : origin_(from), direction_(dir), time_(ti)
  {
  }

  vec3 origin() const { return origin_; }
  vec3 direction() const { return direction_; }
  double time() const { return time_; }
  vec3 point_at_parameter(const double &t) const { return origin_ + direction_ * t; }
};

#endif // RAYTRACER_RAY_H_