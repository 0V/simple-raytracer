#ifndef RAYTRACER_CAMERA_H_
#define RAYTRACER_CAMERA_H_

#include "camera_base.h"
#include "vector_utility.h"
#include "ray.h"

class Camera : public CameraBase
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

  Camera(const double &vfov, const double &aspect)
  {
    double theta = vfov * RadUnit;
    double half_height = std::tan(theta * 0.5);
    double half_width = aspect * half_height;
    lower_left_corner = vec3(-half_width, -half_height, -1.0);
    horizontal = vec3(2 * half_width, 0, 0);
    vertical = vec3(0, 2 * half_height, 0);
    origin = vec3(0, 0, 0);
  }

  Camera(const vec3 &lookfrom, const vec3 &lookat, const vec3 &vup, const double &vfov, const double &aspect)
  {
    vec3 u, v, w;
    double theta = vfov * RadUnit;
    double half_height = std::tan(theta * 0.5);
    double half_width = aspect * half_height;
    origin = lookfrom;
    w = (lookfrom - lookat).normalize();
    u = vup.cross(w).normalize();
    v = w.cross(u);

    lower_left_corner = origin - half_width * u - half_height * v - w;
    horizontal = 2 * half_width * u;
    vertical = 2 * half_height * v;
  }

  Ray get_ray(const double &u, const double &v) const
  {
    return Ray(origin, horizontal * u + vertical * v + lower_left_corner - origin);
  }
};
#endif // RAYTRACER_CAMERA_H_