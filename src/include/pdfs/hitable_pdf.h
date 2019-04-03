#ifndef RAYTRACER_PDFS_HITABLE_PDF_H_
#define RAYTRACER_PDFS_HITABLE_PDF_H_

#include "vector_utility.h"
#include "point_sampler_mc.h"
#include "pdf_base.h"
#include "onb.h"

class HitablePdf : public PdfBase
{
private:
  HitablePtr ptr_;
  vec3 origin_;

public:
  HitablePdf(const HitablePtr &ptr, const vec3 &origin) : ptr_(ptr), origin_(origin)
  {
  }

  virtual double value(const vec3 &direction) const
  {
    return ptr_->pdf_value(origin_, direction);
  }
  virtual vec3 generate() const
  {
    return ptr_->random(origin_);
  }
};
#endif // RAYTRACER_PDFS_HITABLE_PDF_H_