#ifndef RAYTRACER_MATERIALS_LAMBERTIAN_H_
#define RAYTRACER_MATERIALS_LAMBERTIAN_H_

#include <random>
#include "objects/hitable_base.h"

class Lambertian : public MaterialBase
{
private:
  static std::random_device seed_gen_;
  static std::mt19937 engine_;
  static std::uniform_real_distribution<double> dist_;
  
  vec3 sample_point_in_unit_sphere() const
  {
    vec3 p;
    do
    {
      p = vec3(dist_(seed_gen_), dist_(seed_gen_), dist_(seed_gen_));
    } while (p.getSqrLen() >= 1.0);
    return p;
  }

public:
  vec3 albedo;

  Lambertian() {}
  Lambertian(vec3 albedo_) : albedo(albedo_) {}
  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const
  {
    vec3 target = record.normal + sample_point_in_unit_sphere();
    scattered = Ray(record.p, target);
    attenuation = albedo;
    return true;
  }
};

std::random_device Lambertian::seed_gen_ = std::random_device();
std::mt19937 Lambertian::engine_ = std::mt19937(seed_gen_());
std::uniform_real_distribution<double> Lambertian::dist_ = std::uniform_real_distribution<double>(-1, 1);

#endif // RAYTRACER_MATERIALS_LAMBERTIAN_H_