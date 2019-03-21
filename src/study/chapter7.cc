#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include "simple_raytracer.h"

class IHitable;
typedef std::shared_ptr<IHitable> IHitablePtr;

const vec3 SphereCenter(0, 0, -1);
const vec3 OneAll(1.0, 1.0, 1.0);
const vec3 OneX(1.0, 0, 0);
const vec3 ColorMax(0.5, 0.7, 1.0);
const vec3 Yellow(1, 1, 0);
const vec3 White(1, 1, 1);

std::random_device seed_gen;
std::mt19937 engine(seed_gen());
std::uniform_real_distribution<double> dist(-1, 1);

vec3 sample_point_in_unit_sphere()
{
  vec3 p;
  do
  {
    p = vec3(dist(seed_gen), dist(seed_gen), dist(seed_gen));
  } while (p.getSqrLen() >= 1.0);
  return p;
}

vec3 color(const Ray &r, IHitable &world)
{
  HitRecord record;

  if (world.hit(r, 0, INFINITY, record))
  {
    vec3 target = record.p + record.normal + sample_point_in_unit_sphere();
    return 0.5 * color(Ray(record.p, target), world);
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
  constexpr int nx = 200;
  constexpr int ny = 100;
  constexpr int sampling_count = 100;

  // ** FILE ** //
  std::ofstream image("image.ppm");
  image << "P3"
        << "\n";
  image << nx << " " << ny << "\n";
  image << 255 << "\n";
  // ** FILE ** //

  std::vector<HitablePtr> list;
  list.emplace_back(std::make_shared<Sphere>(SphereCenter, 0.5));
  list.emplace_back(std::make_shared<Sphere>(vec3(0, -100.5, -1), 100));
  HitableList hitables(list);

  Camera camera;

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      vec3 col(0, 0, 0);
      for (int s = 0; s < sampling_count; s++)
      {
        double u = (double)(i + dist(engine)) / nx;
        double v = (double)(j + dist(engine)) / ny;
        col += color(camera.get_ray(u, v), hitables);
      }

      col /= (double)sampling_count;
      int ir = 255.99 * col[0];
      int ig = 255.99 * col[1];
      int ib = 255.99 * col[2];
      image << ir << " " << ig << " " << ib << "\n";
    }
  }
}
