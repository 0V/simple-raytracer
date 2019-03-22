#ifndef RAYTRACER_CAMERA_BASE_H_
#define RAYTRACER_CAMERA_BASE_H_

#include <memory>
#include "ray.h"

constexpr double RadUnit = M_PI / 180.0;

class CameraBase;
using CameraPtr = std::shared_ptr<CameraBase>;

class CameraBase
{
public:
  virtual Ray get_ray(const double &u, const double &v) const = 0;
};

#endif // RAYTRACER_CAMERA_BASE_H_