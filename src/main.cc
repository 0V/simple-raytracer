#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include "simple_raytracer.h"

// const vec3 SphereCenter(0, 0, -1);
const vec3 OneAll(1.0, 1.0, 1.0);
const vec3 OneX(1.0, 0, 0);
const vec3 ColorMax(0.5, 0.7, 1.0);
const vec3 Yellow(1, 1, 0);
const vec3 White(1, 1, 1);
const vec3 Black(0, 0, 0);
const vec3 HalfAlbedo(0.5, 0.5, 0.5);

std::random_device seed_gen;
std::mt19937 engine(seed_gen());
std::uniform_real_distribution<double> dist(-1, 1);

constexpr double IgnoreLengthNearCamera = 0.00001;

vec3 color(const Ray &r, HitableBase &world, int depth)
{
  HitRecord record;

  if (world.hit(r, IgnoreLengthNearCamera, INFINITY, record))
  {

    Ray scattered;
    vec3 aten;
    if (depth < 50 && record.mat_ptr->scatter(r, record, aten, scattered))
    {
      return aten.product(color(scattered, world, (depth + 1)));
    }
    else
    {
      return Black;
    }
    //    std::cout << target << "\n";
  }
  else
  {
    vec3 dir_unit = r.direction().normalize();
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

  MaterialPtr lambertian = std::make_shared<Lambertian>(vec3(0.8, 0.3, 0.3));
  MaterialPtr lambertian2 = std::make_shared<Lambertian>(vec3(1, 1, 0.3));
  MaterialPtr lambertian3 = std::make_shared<Lambertian>(vec3(0.3, 1, 0.3));

  MaterialPtr metal = std::make_shared<Metal>(0.8 * OneAll);
  MaterialPtr metal2 = std::make_shared<Metal>(vec3(0.7, 0.7, 1));
  MaterialPtr metal3 = std::make_shared<Metal>(vec3(0.4, 1, 0.4));
  MaterialPtr metal4 = std::make_shared<Metal>(0.8 * OneAll, 0.8);

  std::vector<HitablePtr> list;
  list.emplace_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5, lambertian));
  list.emplace_back(std::make_shared<Sphere>(vec3(1, 0, -1), 0.3, metal));
  list.emplace_back(std::make_shared<Sphere>(vec3(-1, 0, -1), 0.3, metal4));
  list.emplace_back(std::make_shared<Sphere>(vec3(0, -100.5, -1), 100, lambertian3));
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
        col += color(camera.get_ray(u, v), hitables, 0);
      }

      col /= (double)sampling_count;
      int ir = 255.99 * std::sqrt(col[0]);
      int ig = 255.99 * std::sqrt(col[1]);
      int ib = 255.99 * std::sqrt(col[2]);
      image << ir << " " << ig << " " << ib << "\n";
    }
  }
}
