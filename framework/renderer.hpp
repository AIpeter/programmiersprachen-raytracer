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
#define _USE_MATH_DEFINES

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include <cmath>
#include <map>
#include <vector>
#include <cstdlib>
#include <string>
#include <limits>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <light.hpp>

class Renderer
{
public:
  Renderer();
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer(unsigned w, unsigned h,
            std::string const& file, Camera cam, bool aa);

  Ray ComputeCameraRay(float i, float j);
  void filename(std::string const& filename);
  void render();
  void render(std::map<std::string, Shape*> const& shapes, std::vector<Light> const& lights);
  Color render(float x, float y, std::map<std::string, Shape*> const& shapes, std::vector<Light> const& lights);
  // void render(std::map<std::string, Shape*> const& shapes, std::vector<Light> const& lights);
  void write(Pixel const& p);
  void colorNorm(Color & color);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  bool aa;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
  Camera cam_;
};

#endif // #ifndef BUW_RENDERER_HPP
