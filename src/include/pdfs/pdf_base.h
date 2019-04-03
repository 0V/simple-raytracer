#ifndef RAYTRACER_PDFS_PDF_BASE_H_
#define RAYTRACER_PDFS_PDF_BASE_H_

#include "vector_utility.h"

class PdfBase;
using PdfPtr = std::shared_ptr<PdfBase>;

class PdfBase
{
  public:
  virtual double value(const vec3 &direction) const = 0;
  virtual vec3 generate() const = 0;
};

#endif // RAYTRACER_PDFS_PDF_BASE_H_