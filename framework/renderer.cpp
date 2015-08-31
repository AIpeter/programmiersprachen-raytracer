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
  cam_(Camera()),
  aa(false)
  {}

Renderer::Renderer(unsigned w, unsigned h, std::string const& file):
  width_(w),
  height_(h),
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)),
  filename_(file),
  ppm_(width_, height_),
  cam_(Camera()),
  aa(false)
  {}

Renderer::Renderer(unsigned w, unsigned h,
                    std::string const& file, Camera cam, bool aa):
  width_(w),
  height_(h),
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)),
  filename_(file),
  ppm_(width_, height_),
  cam_(cam),
  aa(aa)
  {}

Ray Renderer::ComputeCameraRay(float i, float j)
{
  float norm_i = (i/width_) - 0.5;
  float norm_j = (j/height_) - 0.5;
  float aspect = (float) width_/ (float) height_;
  float fov = cam_.getFov_x() * (M_PI/180.0);
  glm::vec3 image_point = norm_i * aspect * glm::tan(fov/2.0f) * cam_.getCamRight()
                        + norm_j * glm::tan(fov/2.0f) * cam_.getCamUp()
                        + cam_.getDirection();
  return Ray{cam_.getPosition(), image_point};
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

void Renderer::render(std::map<std::string, 
                      std::shared_ptr<Shape>> const& shapes,
                      std::vector<Light> const& lights)
{
  for (unsigned y = 0; y < height_; ++y)
  {
    for (unsigned x = 0; x < width_; ++x)
    {
      Pixel p(x,y);

      if(aa == true)
      {
        std::vector<Color> colors;
        
        colors.push_back(render(x, y, shapes, lights));
        colors.push_back(render(x-0.25, y-0.25, shapes, lights));
        colors.push_back(render(x+0.25, y-0.25, shapes, lights));
        colors.push_back(render(x-0.25, y+0.25, shapes, lights));
        colors.push_back(render(x+0.25, y+0.25, shapes, lights));

        Color accumulate{0.0, 0.0, 0.0};

        for (auto i: colors)
        {
          accumulate += i;
        }

        p.color = accumulate / 5.f;
        colorNorm(p.color);
      }
      else
      {
        p.color = render(x, y, shapes, lights);
      }
      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::colorNorm(Color & color)
{
  color.r = std::min(color.r, 1.f);
  color.g = std::min(color.g, 1.f);
  color.b = std::min(color.b, 1.f);
  color.r = std::max(color.r, 0.f);
  color.g = std::max(color.g, 0.f);
  color.b = std::max(color.b, 0.f);
}

Color Renderer::render(float x, float y, std::map<std::string,
                        std::shared_ptr<Shape>> const& shapes,
                        std::vector<Light> const& lights)
{
  Color c{0.0, 0.0, 0.0};
  Ray r = ComputeCameraRay(x, y);
  float infinity = std::numeric_limits<float>::infinity();
  float t;
  float tmin = infinity;
  std::shared_ptr<Shape> closest_o = NULL;
  for(auto i : shapes) 
  {
    /*
    glm::vec4 r_origin_4 = i.second->world_transformation_inv() * glm::vec4{r.origin, 1};
    glm::vec4 r_direction_4 = i.second->world_transformation_inv() * glm::vec4{r.direction, 0};
    r.origin = glm::vec3{r_origin_4};
    r.direction = glm::vec3{r_direction_4};
    */
    if(i.second->intersect(r,t).intersect == true)
    {
      if(t < tmin) {
        tmin = t;
        closest_o = i.second;      
      }
    }
  }
  if(closest_o != NULL) 
  {
    for(auto i: lights)
    {
      float shade = 1; // kein Schatten
      glm::vec4 r_origin_4{r.origin, 1};
      glm::vec4 r_direction_4{r.direction, 0};
      r_origin_4 = closest_o->world_transformation_inv() * r_origin_4;
      r_direction_4 = closest_o->world_transformation_inv() * r_direction_4;
      glm::vec3 r_origin_3{r_origin_4};
      glm::vec3 r_direction_3{r_direction_4};
      r_direction_3 = glm::normalize(r_direction_3);
      /*glm::vec4 surfacePoint_4{r_origin_3 + (tmin*r_direction_3), 1};
      surfacePoint_4 = closest_o->world_transformation_inv() * surfacePoint_4;
      glm::vec3 surfacePoint{surfacePoint_4};*/
      glm::vec3 surfacePoint{r_origin_3 + (tmin * r_direction_3)};
      Ray shadowRay{i.getposition(), glm::normalize(surfacePoint - i.getposition())}; 
      // float closest_o_t = tmin;
      // Hit closest_o_hit = closest_o->intersect(r, closest_o_t);
      // Ray shadowRay{i.getposition(), 
      //               glm::normalize(closest_o_hit.intersectionPoint
      //                               - i.getposition())};
      float d;
      float dmin = infinity;
      std::shared_ptr<Shape> closest_o_light = NULL;

      if(closest_o->intersect(shadowRay, d).intersect == true)
      {
        for(auto j : shapes) 
        {
          if(j.second->intersect(shadowRay, d).intersect == true)
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
      std::cout << shade << std::endl;
      Hit tmp = closest_o->intersect(r, tmin);
      /*
      glm::vec4 intersectionPoint_4{tmp.intersectionPoint, 1};
      intersectionPoint_4 = closest_o->world_transformation() * intersectionPoint_4;
      tmp.intersectionPoint = glm::vec3{intersectionPoint_4};
      glm::vec4 normal_4{tmp.normal, 0};
      normal_4 = glm::transpose(closest_o->world_transformation_inv()) * normal_4;
      tmp.normal = glm::vec3{normal_4};
      tmp.normal = glm::normalize(tmp.normal);
      */
      // std::cout << "normal: " << glm::to_string(tmp.normal) << std::endl;
      auto col = closest_o->getLight(tmp, r, i, shade);
      // std::cout << "Color: " << col.r << ", " << col.g << ", " << col.b << std::endl;
      c += col;
    }
  }
  else 
  {
    c = Color{0.0, 0.0, 0.0};
  }
  return c;
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

void Renderer::filename(std::string const& filename)
{
  filename_ = filename;
}