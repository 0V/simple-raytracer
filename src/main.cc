#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include "renderer.h"

int main(int argc, char *argv[])
{
  Renderer renderer;
  if (argc > 1)
  {
    renderer.sampling_count = atoi(argv[1]);
  }
  if (argc > 2)
  {
    renderer.file_name = std::string(argv[2]);
  }
  renderer.render();
}
