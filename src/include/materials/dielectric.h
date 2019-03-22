#ifndef RAYTRACER_MATERIALS_DIELECTRIC_H_
#define RAYTRACER_MATERIALS_DIELECTRIC_H_

#include "vector_utility.h"
#include "objects/hitable_base.h"

class Dielectric : public MaterialBase
{
private:
  mutable std::random_device seed_gen_ = std::random_device();
  mutable std::mt19937 engine_ = std::mt19937(seed_gen_());
  mutable std::uniform_real_distribution<double> dist_ = std::uniform_real_distribution<double>(0, 1);

public:
  // refractive index of object (n_obj / n_space)
  double ref_idx;
  double inverse_ref_idx;

  Dielectric(double ref_idx_) : ref_idx(ref_idx_), inverse_ref_idx(1.0 / ref_idx_) {}

  virtual bool scatter(const Ray &r_in, const HitRecord &record, vec3 &attenuation, Ray &scattered) const
  {
    attenuation = vec3(1, 1, 1);
    double ni_over_nt;
    vec3 refracted;
    vec3 outward_normal;
    double cosine;

    vec3 reflected = reflect(r_in.direction(), record.normal);

    if (r_in.direction() * record.normal > 0) // object to space
    {
      outward_normal = -record.normal;
      ni_over_nt = ref_idx; // n_obj / n_space
      cosine = (r_in.direction().normalize() * record.normal);
      cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
    }
    else // space to object
    {
      outward_normal = record.normal;
      ni_over_nt = inverse_ref_idx; //  n_space / n_obj
      cosine = -(r_in.direction().normalize() * record.normal);
    }

    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
    {
      double prob = schlick_fresnel(cosine, ni_over_nt);
      if (dist_(seed_gen_) < prob)
      {
        scattered = Ray(record.p, reflected);
      }
      else
      {
        scattered = Ray(record.p, refracted);
      }
    }
    else
    {
      scattered = Ray(record.p, reflected);
    }

    return true;
  }
};

#endif // RAYTRACER_MATERIALS_DIELECTRIC_H_