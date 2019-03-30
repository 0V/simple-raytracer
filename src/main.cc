#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include "renderer.h"

inline double pdf(const vec3 &p)
{
  return 0.25 / M_PI;
}

int main()
{
  int N = 1000000;
  double sum = 0;
  PointSamplerUnitSphere sampler;

  for (int i = 0; i < N; i++)
  {
    vec3 d = sampler.sample().normalize();
    double cosine_square = d.z * d.z;
    sum += cosine_square / pdf(d);
  }

  std::cout << "I = " << sum / N << std::endl;
  return 0;

  Renderer renderer;
  renderer.render();
}
