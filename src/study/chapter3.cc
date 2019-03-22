#include <iostream>
#include <cmath>
#include <fstream>
#include "simple_raytracer.h"

const vec3 one_all(1.0, 1.0, 1.0);
const vec3 color_max(0.5, 0.7, 1.0);

vec3 color(const Ray &r)
{
  vec3 dir_unit = r.direction().normalize();
  double t = 0.5 * (dir_unit.y + 1.0);
//  double t = (std::cos(3.14 * (dir_unit.y + 1.0)) + 1) * 0.5;
  return (1.0 - t) * one_all + t * color_max;
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
