#ifndef RAYTRACER_MATERIALS_LAMBERTIAN_H_
#define RAYTRACER_MATERIALS_LAMBERTIAN_H_

#include "objects/hitable_base.h"
#include "textures/constant_texture.h"
#include "point_sampler_mc.h"
#include "onb.h"
#include "pdfs/lambert_pdf.h"

class Lambertian : public MaterialBase
{
private:
  PointSamplerLambertian sampler;

public:
  TexturePtr albedo;

  Lambertian() {}
  Lambertian(const TexturePtr &albedo_) : albedo(albedo_) {}
  virtual bool scatter(const Ray &r_in, const HitRecord &hrec, ScatteredRecord &dist)  const
  {
    dist.is_specular = false;
    dist.attenuation = albedo->value(hrec.u, hrec.v, hrec.p);;
    dist.pdf_ptr = std::make_shared<LambertPdf>(hrec.normal);
    return true;

    // vec3 direction;
    // do
    // {
    //   direction = sampler.sample();
    // } while (direction * record.normal < 0);
    // scattered = Ray(record.p, direction.normalize(), r_in.time());
    // alb = albedo->value(record.u, record.v, record.p);
    // pdf = 0.5 * M_1_PI;
    // return true;

    // vec3 direction = record.normal + sampler.sample();
    // scattered = Ray(record.p, direction, r_in.time());
    // alb = albedo->value(record.u, record.v, record.p);
    // pdf = record.normal * scattered.direction() * M_1_PI;
    // return true;
  }

  virtual double scattering_pdf(const Ray &r_in, const HitRecord &record, const Ray &scattered) const
  {
    double cosine = record.normal * scattered.direction().normalize();
    if (cosine < 0)
      cosine = 0;

    return cosine * M_1_PI;
  }
};
#endif // RAYTRACER_MATERIALS_LAMBERTIAN_H_