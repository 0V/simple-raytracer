#include <iostream>
#include <cmath>
#include <fstream>
#include "simple_raytracer.h"

const vec3 SphereCenter(0, 0, -1);
const vec3 OneAll(1.0, 1.0, 1.0);
const vec3 OneX(1.0, 0, 0);
const vec3 ColorMax(0.5, 0.7, 1.0);
const vec3 Yellow(1, 1, 0);
const vec3 White(1, 1, 1);

double hit_sphere(const vec3 &center, const double &radius, const Ray &r)
{
  vec3 o_to_center = r.origin() - center;
  // ax^2 + bt + c
  //
  double a = r.direction() * r.direction();
  double b = 2 * (r.direction() * o_to_center);
  double c = o_to_center * o_to_center - radius * radius;
  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0)
  {
    return -1;
  }
  else
  {
    return (-b - std::sqrt(discriminant)) * 0.5 / a;
  }
}

vec3 color(const Ray &r)
{
  double t = hit_sphere(SphereCenter, 0.5, r);
  if (t > 0)
  {
    vec3 normal = (r.point_at_parameter(t) - SphereCenter).getUnit();
    double d = -(normal * r.direction().getUnit());
    return (1 - d) * Yellow + d * White;
  }
  vec3 dir_unit = r.direction().getUnit();
  t = 0.5 * (dir_unit.y + 1.0);
  //  double t = (std::cos(3.14 * (dir_unit.y + 1.0)) + 1) * 0.5;
  return (1.0 - t) * OneAll + t * ColorMax;
}

int main()
{
  // ** FILE ** //
  std::ofstream image("image.ppm");
  int nx = 200;
  int ny = 100;
  image << "P3"
        << "\n";
  image << nx << " " << ny << "\n";
  image << 255 << "\n";
  // ** FILE ** //

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0, 0);
  vec3 vertical(0, 2.0, 0);
  vec3 origin(0, 0, 0);

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      double u = (double)i / nx;
      double v = (double)j / ny;
      Ray ray_to_p(origin, horizontal * u + vertical * v + lower_left_corner);
      vec3 col = color(ray_to_p);
      int ir = 255.99 * col[0];
      int ig = 255.99 * col[1];
      int ib = 255.99 * col[2];
      image << ir << " " << ig << " " << ib << "\n";
    }
  }
}
