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

vec3 color(const Ray &r, IHitable &world)
{
  HitRecord record;

  if (world.hit(r, 0, INFINITY, record))
  {
    return 0.5 * (record.normal + OneAll);
  }
  else
  {
    vec3 dir_unit = r.direction().getUnit();
    double t = 0.5 * (dir_unit.y + 1.0);
    return (1.0 - t) * OneAll + t * ColorMax;
  }
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

  IHitable *tmp_hitables[2];

  tmp_hitables[0] = new Sphere(SphereCenter, 0.5);
  tmp_hitables[1] = new Sphere(vec3(0, -100.5, -1), 100);

  HitableList hitables(tmp_hitables, 2);

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      double u = (double)i / nx;
      double v = (double)j / ny;
      Ray ray_to_p(origin, horizontal * u + vertical * v + lower_left_corner);
      vec3 col = color(ray_to_p, hitables);
      int ir = 255.99 * col[0];
      int ig = 255.99 * col[1];
      int ib = 255.99 * col[2];
      image << ir << " " << ig << " " << ib << "\n";
    }
  }
}
