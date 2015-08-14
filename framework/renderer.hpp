// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include <string>
#include <limits>
#include <glm/glm.hpp>

class Renderer
{
public:
  Renderer();
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer(unsigned w, unsigned h,
            std::string const& file, Camera cam);

  Ray ComputeCameraRay(int i, int j);
  void render();
  void render(std::vector<Shape*> const& shapes);
  void write(Pixel const& p);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
  Camera cam_;
};

#endif // #ifndef BUW_RENDERER_HPP
