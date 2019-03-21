#include <fstream>
#include "simple_raytracer.h"

void HelloImage()
{  std::ofstream image("image.ppm");
  int nx = 200;
  int ny = 100;

  image << "P3"
        << "\n";
  image << nx << " " << ny << "\n";
  image << 255 << "\n";
  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      vec3 col(double(i) / double(nx), double(j) / double(ny), 0.2);
      int ir = 255.99 * col[0];
      int ig = 255.99 * col[1];
      int ib = 255.99 * col[2];
      image << ir << " " << ig << " " << ib << "\n";
    }
  }

}