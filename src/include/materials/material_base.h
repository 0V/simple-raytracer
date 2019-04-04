#ifndef RAYTRACER_MATERIALS_MATERIAL_BASE_H_
#define RAYTRACER_MATERIALS_MATERIAL_BASE_H_

struct HitRecord;
struct ScatteredRecord;


#include "vector_utility.h"
#include "objects/hitable_base.h"
#include "pdfs/pdf_base.h"


struct ScatteredRecord
{
  Ray specular_ray;
  bool is_specular;
  vec3 attenuation;
  PdfPtr pdf_ptr;
};

class MaterialBase
{
public:
  virtual bool scatter(const Ray &r_in, const HitRecord &record, ScatteredRecord &dist) const
  {
    return false;
  }

  virtual double scattering_pdf(const Ray &r_in, const HitRecord &record, const Ray &scattered) const
  {
    return false;
  }
  virtual vec3 emitted(const Ray &r_in, const HitRecord &record, const double &u, const double &v, const vec3 &p) const
  {
    return Vectors::Zero;
  };
};

using MaterialPtr = std::shared_ptr<MaterialBase>;

#endif // RAYTRACER_MATERIALS_MATERIAL_BASE_H_
