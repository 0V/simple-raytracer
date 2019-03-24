#ifndef RAYTRACER_TEXTURES_IMAGE_TEXTURES_H_
#define RAYTRACER_TEXTURES_IMAGE_TEXTURES_H_

#include "texture_base.h"
#include "ray.h"

using ImagePtr = std::shared_ptr<unsigned char[]>;

class ImageTexture : public TextureBase
{
private:
  vec3 color_;
  ImagePtr pixels_;
  int nx_, ny_;

public:
  ImageTexture() {}
  ImageTexture(const ImagePtr &pixels, const int &width, const int &height) : pixels_(pixels), nx_(width), ny_(height) {}

  virtual vec3 value(const double &u, const double &v, const vec3 &p) const
  {
    int i = (u)*nx_;
    int j = (1 - v) * ny_ - 0.001;
    if (i < 0)
    {
      i = 0;
    }
    if (j < 0)
    {
      j = 0;
    }
    if (i > nx_ - 1)
    {
      i = nx_ - 1;
    }
    if (i > ny_ - 1)
    {
      j = ny_ - 1;
    }

    double r = (int)pixels_[3 * i * 3 * nx_ * j] / 255.0;
    double g = (int)pixels_[3 * i * 3 * nx_ * j + 1] / 255.0;
    double b = (int)pixels_[3 * i * 3 * nx_ * j + 2] / 255.0;

    return vec3(r, g, b);
  }
};
#endif // RAYTRACER_TEXTURES_IMAGE_TEXTURES_H_