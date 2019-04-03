#ifndef RAYTRACER_PDFS_LAMBERT_PDF_H_
#define RAYTRACER_PDFS_LAMBERT_PDF_H_

#include "vector_utility.h"
#include "point_sampler_mc.h"
#include "pdf_base.h"
#include "onb.h"

class LambertPdf : public PdfBase
{
private:
  Onb uvw_;
  PointSamplerLambertian smapler_;

public:
  LambertPdf(const vec3 &w) : uvw_(w) {}

  virtual double value(const vec3 &direction) const
  {
    double cosine = direction.normalize() * uvw_.w();
    if (cosine > 0)
    {
      return cosine * M_1_PI;
    }
    else
    {
      return 0;
    }
  }

  virtual vec3 generate() const
  {
    return uvw_.local(smapler_.sample());
  }
};
#endif // RAYTRACER_PDFS_LAMBERT_PDF_H_