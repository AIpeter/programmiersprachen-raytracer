// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer():
  width_(200),
  height_(200),
  colorbuffer_(width_*height_, Color{0.0, 0.0, 0.0}),
  filename_("standard.ppm"),
  ppm_(width_, height_),
  cam_(Camera())
  {}

Renderer::Renderer(unsigned w, unsigned h, std::string const& file):
  width_(w),
  height_(h),
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)),
  filename_(file),
  ppm_(width_, height_),
  cam_(Camera())
  {}

Renderer::Renderer(unsigned w, unsigned h,
                    std::string const& file, Camera cam):
  width_(w),
  height_(h),
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)),
  filename_(file),
  ppm_(width_, height_),
  cam_(cam)
  {}

Ray Renderer::ComputeCameraRay(float i, float j)
{
  float norm_i = (i/width_) - 0.5;
  float norm_j = (j/height_) - 0.5;
  glm::vec3 image_point = norm_i * cam_.getCamRight()
                        + norm_j * cam_.getCamUp()
                        + cam_.getPosition()
                        + cam_.getDirection();
  glm::vec3 ray_dir = image_point - cam_.getPosition();
  return Ray{cam_.getPosition(), ray_dir}; 
}

void Renderer::render() {
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }
      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::render(std::map<std::string, Shape*> const& shapes, std::vector<Light> const& lights)
{
  float aspect = (float) width_ / (float) height_;
  for (unsigned y = 0; y < height_; ++y) 
  {
    for (unsigned x = 0; x < width_; ++x) 
    {
      Pixel p(x,y);
      Ray r = ComputeCameraRay(x*aspect, y);
      //std::cout << "Direction = " << r.direction.x << "; " << r.direction.y << "; " << r.direction.z << "\n";
      float infinity = std::numeric_limits<float>::infinity();
      float t;
      float tmin = infinity;
      Shape* closest_o = NULL;
      for(auto i : shapes) 
      {
        if(i.second->intersect(r, t) == true)
        {
          if(t < tmin) {
            tmin = t;
            closest_o = i.second;
          }
          /*
          if(i->closer_z() > tmin) 
          {
            tmin = i->closer_z();
            closest_o = i;
          }
          */
          // std::cout << t << std::endl;
        }
      }
      if(closest_o != NULL) 
      {
        for(auto i: lights)
        {
          float shade = 1; // kein Schatten
          glm::vec3 surfacePoint{tmin*r.direction};
          Ray shadowRay{i.getposition(), glm::normalize(surfacePoint - i.getposition())};
          float d;
          float dmin = infinity;
          Shape* closest_o_light = NULL;

          if(closest_o->intersect(shadowRay, d) == true)
          {
            for(auto j : shapes) 
            {
              if(j.second->intersect(shadowRay, d) == true)
              {
                if(d < dmin) 
                {
                  dmin = d;
                  closest_o_light = j.second;
                }
              }
            }
            if(closest_o_light != closest_o)
            {
              shade = 0;
            }
          } 
          p.color += closest_o->getLight(tmin, r, i, shade);
        }
      }
      else 
      {
        p.color = Color{0.0, 0.0, 0.0};
      }
      write(p);
    }
  }
  ppm_.save(filename_);

}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
