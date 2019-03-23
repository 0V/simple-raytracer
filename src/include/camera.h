#ifndef RAYTRACER_DOF_CAMERA_H_
#define RAYTRACER_DOF_CAMERA_H_

#include "camera_base.h"
#include "vector_utility.h"
#include "point_sampler_disk.h"
#include "ray.h"

class Camera : public CameraBase
{

private:
  PointSamplerUnitDisk sampler;

  mutable std::random_device seed_gen_ = std::random_device();
  mutable std::mt19937 engine_ = std::mt19937(seed_gen_());
  mutable std::uniform_real_distribution<double> dist_ = std::uniform_real_distribution<double>(0, 1);

public:
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 origin;
  vec3 du, dv, dw;
  double lens_radius;
  double time0, time1, time_range;

  Camera(const vec3 &lookfrom, const vec3 &lookat, const vec3 &vup,
         const double &vfov, const double &aspect, const double &aperture, const double &focus_dist,
         const double &t0, const double &t1)
  {
    time0 = t0;
    time1 = t1;
    time_range = t1 - t0;
    lens_radius = aperture * 0.5;
    double theta = vfov * RadUnit;
    double half_height = std::tan(theta * 0.5);
    double half_width = aspect * half_height;
    origin = lookfrom;
    dw = (lookfrom - lookat).normalize();
    du = vup.cross(dw).normalize();
    dv = dw.cross(du);

    lower_left_corner = origin - focus_dist * (half_width * du + half_height * dv + dw);
    horizontal = 2 * focus_dist * half_width * du;
    vertical = 2 * focus_dist * half_height * dv;
  }

  Ray get_ray(const double &u, const double &v) const
  {
    vec3 rd = lens_radius * sampler.sample();
    vec3 offset = du * rd.x + dv * rd.y;
    double t = time0 + dist_(engine_) * time_range;
    return Ray(origin + offset, horizontal * u + vertical * v + lower_left_corner - origin - offset, t);
  }
};

#endif // RAYTRACER_DOF_CAMERA_H_