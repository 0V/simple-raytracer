#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include "simple_raytracer.h"
#include "camera.h"

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
std::uniform_real_distribution<double> dist_01(0, 1);

constexpr double IgnoreLengthNearCamera = 0.00001;
constexpr int DepthCount = 20;
//constexpr int DepthCount = 50;

vec3 color(const Ray &r, HitableBase &world, int depth)
{
  HitRecord record;

  if (world.hit(r, IgnoreLengthNearCamera, INFINITY, record))
  {

    Ray scattered;
    vec3 aten;
    vec3 emitted = record.mat_ptr->emitted(record.u, record.v, record.p);
    if (depth < DepthCount && record.mat_ptr->scatter(r, record, aten, scattered))
    {
      return emitted + aten.product(color(scattered, world, (depth + 1)));
    }
    else
    {
      return emitted;
    }
  }
  else
  {
    return Vectors::Zero;
    // vec3 dir_unit = r.direction().normalize();
    // double t = 0.5 * (dir_unit.y + 1.0);
    // return (1.0 - t) * OneAll + t * ColorMax;
  }
}

std::vector<HitablePtr> random_scene()
{
  std::vector<HitablePtr> list;
  // TexturePtr even = std::make_shared<ConstantTexture>(OneAll * 0.1);
  // TexturePtr odd = std::make_shared<ConstantTexture>(OneAll * 0.8);
  // TexturePtr lambert_tex = std::make_shared<CheckerTexture>(even, odd);
  TexturePtr lambert_tex = std::make_shared<PerlinNoiseTexture>(1);
  list.emplace_back(std::make_shared<Sphere>(vec3(0, -1000, 0), 1000, std::make_shared<Lambertian>(lambert_tex)));

  for (int a = -6; a < 6; a++)
  {
    for (int b = -6; b < 6; b++)
    {
      float choose_mat = dist_01(engine);
      vec3 center(a + 0.9 * dist_01(engine), 0.2, b + 0.9 * dist_01(engine));
      if ((center - vec3(4, 0.2, 0)).length() > 0.9)
      {
        if (choose_mat < 0.8)
        {
          list.emplace_back(std::make_shared<Sphere>(center, 0.2,
                                                     std::make_shared<Lambertian>(
                                                         std::make_shared<ConstantTexture>(
                                                             vec3(dist_01(engine) * dist_01(engine),
                                                                  dist_01(engine) * dist_01(engine),
                                                                  dist_01(engine) * dist_01(engine))))));

          // list.emplace_back(std::make_shared<MovingSphere>(center, center + vec3(0, 0.5 * dist_01(engine), 0),
          //                                                  0, 1, 0.2,
          //                                                  std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(
          //                                                      vec3(dist_01(engine) * dist_01(engine),
          //                                                           dist_01(engine) * dist_01(engine),
          //                                                           dist_01(engine) * dist_01(engine))))));
        }
        else if (choose_mat < 0.95)
        {
          list.emplace_back(std::make_shared<Sphere>(center, 0.2, std::make_shared<Metal>(vec3(0.5 * (1 + dist_01(engine)), 0.5 * (1 + dist_01(engine)), 0.5 * (1 + dist_01(engine))), 0.5 * dist_01(engine))));
        }
        else
        {
          list.emplace_back(std::make_shared<Sphere>(center, 0.2, std::make_shared<Dielectric>(1.5)));
        }
      }
    }
  }

  list.emplace_back(std::make_shared<Sphere>(vec3(0, 1, 0), 1.0, std::make_shared<Dielectric>(1.5)));
  list.emplace_back(std::make_shared<Sphere>(vec3(-4, 1, 0), 1.0, std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(vec3(0.4, 0.2, 0.1)))));
  list.emplace_back(std::make_shared<Sphere>(vec3(4, 1, 0), 1.0, std::make_shared<Metal>(vec3(0.7, 0.6, 0.5), 0.0)));

  return list;
}

std::vector<HitablePtr> two_perlin_sphere()
{
  std::vector<HitablePtr> list;
  TexturePtr lambert_tex = std::make_shared<PerlinNoiseTurbTexture>(1);
  list.emplace_back(std::make_shared<Sphere>(vec3(0, -1000, 0), 1000, std::make_shared<Lambertian>(lambert_tex)));
  list.emplace_back(std::make_shared<Sphere>(vec3(0, 2, 0), 2, std::make_shared<Lambertian>(lambert_tex)));
  return list;
}

std::vector<HitablePtr> two_perlin_sphere_light()
{
  std::vector<HitablePtr> list;
  TexturePtr lambert_tex = std::make_shared<PerlinNoiseTurbTexture>(1);

  TexturePtr const_tex = std::make_shared<ConstantTexture>(vec3(4, 4, 4));
  MaterialPtr light_mat = std::make_shared<DiffuseLight>(const_tex);

  list.emplace_back(std::make_shared<Sphere>(vec3(0, -1000, 0), 1000, std::make_shared<Lambertian>(lambert_tex)));
  list.emplace_back(std::make_shared<Sphere>(vec3(0, 2, 0), 2, std::make_shared<Lambertian>(lambert_tex)));
  //  list.emplace_back(std::make_shared<Sphere>(vec3(0, 7, 0), 2, light_mat));
  //  list.emplace_back(std::make_shared<RectangleXY>(3, 5, 1, 3, -2, light_mat));
  list.emplace_back(std::make_shared<RectangleYZ>(-1, 1, -1, 1, -2, light_mat));
  // list.emplace_back(std::make_shared<RectangleZX>(3, 5, 1, 3, -2, light_mat));
  return list;
}

std::vector<HitablePtr> cornell_box()
{
  std::vector<HitablePtr> list;

  MaterialPtr red_mat = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(vec3(0.65, 0.05, 0.05)));
  MaterialPtr white_mat = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(vec3(0.73, 0.73, 0.73)));
  MaterialPtr green_mat = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(vec3(0.12, 0.45, 0.15)));
  MaterialPtr light_mat = std::make_shared<DiffuseLight>(std::make_shared<ConstantTexture>(Vectors::One * 15));

  list.emplace_back(std::make_shared<FlipNormals>(std::make_shared<RectangleYZ>(0, 555, 0, 555, 555, green_mat)));
  list.emplace_back(std::make_shared<RectangleYZ>(0, 555, 0, 555, 0, red_mat));
  list.emplace_back(std::make_shared<RectangleXZ>(213, 343, 227, 332, 554, light_mat));
  list.emplace_back(std::make_shared<FlipNormals>(std::make_shared<RectangleXZ>(0, 555, 0, 555, 555, white_mat)));
  list.emplace_back(std::make_shared<RectangleXZ>(0, 555, 0, 555, 0, white_mat));
  list.emplace_back(std::make_shared<FlipNormals>(std::make_shared<RectangleXY>(0, 555, 0, 555, 555, white_mat)));

  auto box_g = std::make_shared<Box>(vec3(0, 0, 0), vec3(165, 165, 165), white_mat);
  list.emplace_back(Transform::Translate::create(Transform::RotateY::create(box_g, -18), vec3(139, 0, 65)));

  auto box_r = std::make_shared<Box>(vec3(0, 0, 0), vec3(165, 330, 165), white_mat);
  list.emplace_back(Transform::Translate::create(Transform::RotateY::create(box_r, 15), vec3(265, 0, 295)));
  //  list.emplace_back(Transform::Translate::create(box_r, vec3(100, 0, 0)));

  return list;
}

// std::vector<HitablePtr> two_image_sphere()
// {
//   int nx, ny, nn;
//   std::vector<HitablePtr> list;
//   unsigned char *tex_data = stbi_load("earth.jpg", &nx, &ny, &nn, 0);
//   TexturePtr lambert_tex = std::make_shared<ImageTexture>(tex_data, nx, ny);
//   list.emplace_back(std::make_shared<Sphere>(vec3(0, -1000, 0), 1000, std::make_shared<Lambertian>(lambert_tex)));
//   list.emplace_back(std::make_shared<Sphere>(vec3(0, 2, 0), 2, std::make_shared<Lambertian>(lambert_tex)));
//   return list;
// }

int main()
{
  constexpr int nx = 820;
  constexpr int ny = 820;
  // constexpr int nx = 1280;
  // constexpr int ny = 720;
  // constexpr int nx = 640;
  // constexpr int ny = 360;
  // constexpr int nx = 160;
  // constexpr int ny = 90;
  constexpr int sampling_count = 500;

  // ** FILE ** //
  std::ofstream image("image.ppm");
  image << "P3"
        << "\n";
  image << nx << " " << ny << "\n";
  image << 255 << "\n";
  // ** FILE ** //

  // MaterialPtr lambertian = std::make_shared<Lambertian>(vec3(0.8, 0.3, 0.3));
  // MaterialPtr lambertian2 = std::make_shared<Lambertian>(vec3(1, 1, 0.3));
  // MaterialPtr lambertian3 = std::make_shared<Lambertian>(vec3(0.3, 1, 0.3));

  // MaterialPtr metal = std::make_shared<Metal>(0.8 * OneAll);
  // MaterialPtr metal2 = std::make_shared<Metal>(vec3(0.7, 0.7, 1));
  // MaterialPtr metal3 = std::make_shared<Metal>(vec3(0.4, 1, 0.4));
  // MaterialPtr metal4 = std::make_shared<Metal>(0.8 * OneAll, 0.8);

  // MaterialPtr dilectric = std::make_shared<Dielectric>(1.5);

  // std::vector<HitablePtr> list = random_scene();
  //  std::vector<HitablePtr> list = two_perlin_sphere();
  // std::vector<HitablePtr> list = two_perlin_sphere_light();
  std::vector<HitablePtr> list = cornell_box();
  // std::vector<HitablePtr> list = two_image_sphere();

  /*  list.emplace_back(std::make_shared<Sphere>(vec3(0, 0, -1), 0.5, lambertian));
  list.emplace_back(std::make_shared<Sphere>(vec3(1, 0, -1), 0.3, metal4));
  list.emplace_back(std::make_shared<Sphere>(vec3(0, -100.5, -1), 100, lambertian3));
  list.emplace_back(std::make_shared<Sphere>(vec3(-1, 0, -1), -0.45, dilectric));*/

  HitableList hitables(list);

  //  vec3 lookfrom(-1, 1, 2);
  //  vec3 lookat(0, 0, -1);
  // vec3 lookfrom(23, 23, 3);
  // vec3 lookat(0, 0, 0);
  vec3 lookfrom(278, 278, -800);
  vec3 lookat(278, 278, 0);
  double vfov = 40.0;
  double dist_to_focus = 10.0;
  double aperture = 0;
  //  CameraPtr camera = std::make_shared<RaeCamera>(120, 2);
  // CameraPtr camera = std::make_shared<RaeCamera>(lookfrom, lookat, vec3(0, 1, 0), 90, (double)nx / ny);

  CameraPtr camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0, 1, 0), vfov, double(nx) / double(ny), aperture, dist_to_focus, 0, 1);
  //  camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, double(nx) / double(ny), aperture, dist_to_focus);

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      vec3 col(0, 0, 0);
      for (int s = 0; s < sampling_count; s++)
      {
        double u = (double)(i + dist_01(engine)) / nx;
        double v = (double)(j + dist_01(engine)) / ny;
        //        col += color(cam.get_ray(u, v), hitables, 0);
        col += color(camera->get_ray(u, v), hitables, 0);
      }

      col /= (double)sampling_count;
      int ir = 255.99 * std::sqrt(col[0]);
      int ig = 255.99 * std::sqrt(col[1]);
      int ib = 255.99 * std::sqrt(col[2]);
      image << ir << " " << ig << " " << ib << "\n";
    }
  }
}
