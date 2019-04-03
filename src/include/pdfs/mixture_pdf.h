#ifndef RAYTRACER_PDFS_MIXTURE_PDF_H_
#define RAYTRACER_PDFS_MIXTURE_PDF_H_

class MixturePdf : public PdfBase
{
private:
  PdfPtr p0_;
  PdfPtr p1_;
  double p0ratio_;
  double p1ratio_;
  ValueSampler<double> sampler_ = ValueSampler<double>(0, 1);

public:
  MixturePdf(const PdfPtr &p0, const PdfPtr &p1, double p0ratio = 0.5) : p0_(p0), p1_(p1), p0ratio_(p0ratio), p1ratio_(1 - p0ratio)
  {
  }

  virtual double value(const vec3 &direction) const
  {
    return p0ratio_ * p0_->value(direction) + p1ratio_ * p1_->value(direction);
  }
  virtual vec3 generate() const
  {
    if (sampler_.sample() < p0ratio_)
    {
      return p0_->generate();
    }
    else
    {
      return p1_->generate();
    }
  }
};

#endif // RAYTRACER_PDFS_MIXTURE_PDF_H_