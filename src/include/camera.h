#ifndef RAYTRACER_CAMERA_H_
#define RAYTRACER_CAMERA_H_

#include "vector_utility.h"
#include "ray.h"

class Camera
{

public:
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 origin;

  Camera()
  {
    lower_left_corner = vec3(-2.0, -1.0, -1.0);
    horizontal = vec3(4.0, 0, 0);
    vertical = vec3(0, 2.0, 0);
    origin = vec3(0, 0, 0);
  }

  Camera(const vec3 &lower_left_corner_, const vec3 &horizontal_, const vec3 &vertical_, const vec3 &origin_)
      : lower_left_corner(lower_left_corner_), horizontal(horizontal_), vertical(vertical_), origin(origin_)
  {
  }

  Ray get_ray(const double &u, const double &v)
  {
    return Ray(origin, horizontal * u + vertical * v + lower_left_corner);
  }
};
#endif // RAYTRACER_CAMERA_H_