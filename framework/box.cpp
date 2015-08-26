#include "box.hpp"

Box::Box(): // default constructor
  Shape(),
  min_{0, 0, 0},
  max_{1, 1, 1} {}

Box::Box(Box const& b):
  Shape(b.name(), b.mat()),
  min_{b.min()},
  max_{b.max()}
  {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
         std::string const& name, Material const& mat):
  Shape(name, mat),
  min_{min},
  max_{max} {}

float Box::area() const
  {
    return (2*((max_.x-min_.x) * (max_.y-min_.y) +
            (max_.y-min_.y) * (max_.z-min_.z) +
            (max_.x-min_.x) * (max_.z-min_.z)));
  }

float Box::volume() const
{
  return ((max_.x-min_.x) * (max_.x-min_.x) * (max_.x-min_.x));
}

glm::vec3 Box::min() const {return min_;}
glm::vec3 Box::max() const {return max_;}

/* virtual */ std::ostream& Box::print(std::ostream& os) const {
        os << "Box " << name() << ", Minimum (" << min_.x << "," << min_.y
                << "," << min_.z << "), Maximum (" << max_.x << "," << max_.y
                << "," << max_.z << ")" << "\n" << mat();
        return os;
}

bool Box::intersect(Ray const& r, float& t)
{
  bool cut = false;
  auto d = glm::normalize(r.direction);
  float tmin;
  //check x_min-plane:
  t = (min_.x - r.origin.x)/(d.x); //parameter zur berechnung d schnittpunkts x-ebene =po + t * d
  glm::vec3 intersection_xmin = r.origin+(t*d);
  /*std::cout << "intersection_xmin.x = " << intersection_xmin.x << std::endl;
  std::cout << "intersection_xmin.y = " << intersection_xmin.y << std::endl;
  std::cout << "intersection_xmin.z = " << intersection_xmin.z << std::endl;*/
  
  if( intersection_xmin.x >= min_.x && 
    intersection_xmin.x <= max_.x && 
    intersection_xmin.y >= min_.y && 
    intersection_xmin.y <= max_.y && 
    intersection_xmin.z >= min_.z && 
    intersection_xmin.z <= max_.z)
  {
    cut = true;
    tmin = t;
  }
  //check x_max-plane
  t = (max_.x - r.origin.x)/(d.x);
  glm::vec3 intersection_xmax = r.origin+(t*d);
  /*std::cout << "intersection_xmax.x = " << intersection_xmax.x << std::endl;
  std::cout << "intersection_xmax.y = " << intersection_xmax.y << std::endl;
  std::cout << "intersection_xmax.z = " << intersection_xmax.z << std::endl;*/

  if( intersection_xmax.x >= min_.x && 
    intersection_xmax.x <= max_.x && 
    intersection_xmax.y >= min_.y && 
    intersection_xmax.y <= max_.y && 
    intersection_xmax.z >= min_.z && 
    intersection_xmax.z <= max_.z)
  {
    cut = true;
    if(t <= tmin) {
      tmin = t;
    }
  }

  //check y-min-plane
  t = (min_.y - r.origin.y)/(d.y); //parameter zur berechnung d schnittpunkts x-ebene =po + t * d
  glm::vec3 intersection_ymin = r.origin+(t*d);
  /*std::cout << "intersection_ymin.x = " << intersection_ymin.x << std::endl;
  std::cout << "intersection_ymin.y = " << intersection_ymin.y << std::endl;
  std::cout << "intersection_ymin.z = " << intersection_ymin.z << std::endl;*/
  
  if( intersection_ymin.x >= min_.x && 
    intersection_ymin.x <= max_.x && 
    intersection_ymin.y >= min_.y && 
    intersection_ymin.y <= max_.y && 
    intersection_ymin.z >= min_.z && 
    intersection_ymin.z <= max_.z)
  {
    cut = true;
    if(t <= tmin) {
      tmin = t;
    }
  }
  //check y_max-plane
  t = (max_.y - r.origin.y)/(d.y);
  glm::vec3 intersection_ymax = r.origin+(t*d);
  /*std::cout << "intersection_ymax.x = " << intersection_ymax.x << std::endl;
  std::cout << "intersection_ymax.y = " << intersection_ymax.y << std::endl;
  std::cout << "intersection_ymax.z = " << intersection_ymax.z << std::endl;*/

  if( intersection_ymax.x >= min_.x && 
    intersection_ymax.x <= max_.x && 
    intersection_ymax.y >= min_.y && 
    intersection_ymax.y <= max_.y && 
    intersection_ymax.z >= min_.z && 
    intersection_ymax.z <= max_.z)
  {
    cut = true;
    if(t <= tmin) {
      tmin = t;
    }
  }

  //check z_min-plane
  t = (min_.z - r.origin.z)/(d.z); //parameter zur berechnung d schnittpunkts x-ebene =po + t * d
  glm::vec3 intersection_zmin = r.origin+(t*d);
  /*std::cout << "intersection_zmin.x = " << intersection_zmin.x << std::endl;
  std::cout << "intersection_zmin.y = " << intersection_zmin.y << std::endl;
  std::cout << "intersection_zmin.z = " << intersection_zmin.z << std::endl;*/
  
  if( intersection_zmin.x >= min_.x && 
    intersection_zmin.x <= max_.x && 
    intersection_zmin.y >= min_.y && 
    intersection_zmin.y <= max_.y && 
    intersection_zmin.z >= min_.z && 
    intersection_zmin.z <= max_.z)
  {
    cut = true;
    if(t <= tmin) {
      tmin = t;
    }
  }
  //check z_max-plane
  t = (max_.z - r.origin.z)/(d.z);
  glm::vec3 intersection_zmax = r.origin+(t*d);
  /*std::cout << "intersection_zmax.x = " << intersection_zmax.x << std::endl;
  std::cout << "intersection_zmax.y = " << intersection_zmax.y << std::endl;
  std::cout << "intersection_zmax.z = " << intersection_zmax.z << std::endl;*/

  if( intersection_zmax.x >= min_.x && 
    intersection_zmax.x <= max_.x && 
    intersection_zmax.y >= min_.y && 
    intersection_zmax.y <= max_.y && 
    intersection_zmax.z >= min_.z && 
    intersection_zmax.z <= max_.z)
  {
    cut = true;
    if(t <= tmin) {
      tmin = t;
    }
  }
    t = tmin;
    return cut;
}

float Box::closer_z() const
{
  if (max_.z > min_.z) {
    return min_.z;
  }
  else {
    return max_.z;
  }
}

Color Box::getLight(float & d, Ray const& r, Light const& light, float shade) const
{
    float diffuseCos = computeDiffuseArc(*this, d, r, light);
  Color licht = (light.getld() * mat_.kd() * diffuseCos);
   return licht;
}

void Box::translate(glm::vec3 const& direction)
{

}

void Box::scale(glm::vec3 const& scale)
{


}