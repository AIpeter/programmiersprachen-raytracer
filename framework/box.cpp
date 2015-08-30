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

Hit Box::intersect(Ray const& r, float & t)
{
  Hit hit;
  float tmin = std::numeric_limits<float>::infinity();
  bool cut = false;
  auto d = r.direction;
  //check x_min-plane:
  t = (min_.x - r.origin.x)/(d.x); //parameter zur berechnung d schnittpunkts x-ebene =po + t * d
  glm::vec3 intersection_xmin = r.origin+(t*d);
  
  if( intersection_xmin.x >= min_.x && 
    intersection_xmin.x <= max_.x && 
    intersection_xmin.y >= min_.y && 
    intersection_xmin.y <= max_.y && 
    intersection_xmin.z >= min_.z && 
    intersection_xmin.z <= max_.z)
  {
   if(t < tmin)
   {
     tmin = t;
   }
   cut = true;
    
  }
  //check x_max-plane
  t = (max_.x - r.origin.x)/(d.x);
  glm::vec3 intersection_xmax = r.origin+(t*d);

  if( intersection_xmax.x >= min_.x && 
    intersection_xmax.x <= max_.x && 
    intersection_xmax.y >= min_.y && 
    intersection_xmax.y <= max_.y && 
    intersection_xmax.z >= min_.z && 
    intersection_xmax.z <= max_.z)
  {
   if(t < tmin)
   {
     tmin = t;
   }
    cut = true;
    
  }
  

  //check y-min-plane
  t = (min_.y - r.origin.y)/(d.y); //parameter zur berechnung d schnittpunkts x-ebene =po + t * d
  glm::vec3 intersection_ymin = r.origin+(t*d);

  if( intersection_ymin.x >= min_.x && 
    intersection_ymin.x <= max_.x && 
    intersection_ymin.y >= min_.y && 
    intersection_ymin.y <= max_.y && 
    intersection_ymin.z >= min_.z && 
    intersection_ymin.z <= max_.z)
  {
   if(t < tmin)
   {
     tmin = t;
   }
    cut = true;
    
  }
  
  //check y_max-plane
  t = (max_.y - r.origin.y)/(d.y);
  glm::vec3 intersection_ymax = r.origin+(t*d);

  if( intersection_ymax.x >= min_.x && 
    intersection_ymax.x <= max_.x && 
    intersection_ymax.y >= min_.y && 
    intersection_ymax.y <= max_.y && 
    intersection_ymax.z >= min_.z && 
    intersection_ymax.z <= max_.z)
  {
   if(t < tmin)
   {
     tmin = t;
   }
    cut = true;
    
  }
   
  //check z_min-plane
  t = (min_.z - r.origin.z)/(d.z); //parameter zur berechnung d schnittpunkts x-ebene =po + t * d
  glm::vec3 intersection_zmin = r.origin+(t*d);
  
  if( intersection_zmin.x >= min_.x && 
    intersection_zmin.x <= max_.x && 
    intersection_zmin.y >= min_.y && 
    intersection_zmin.y <= max_.y && 
    intersection_zmin.z >= min_.z && 
    intersection_zmin.z <= max_.z)
  {
   if(t < tmin)
   {
     tmin = t;
   }
    cut = true;
    
  }
  
  //check z_max-plane
  t = (max_.z - r.origin.z)/(d.z);
  glm::vec3 intersection_zmax = r.origin+(t*d);

  if( intersection_zmax.x >= min_.x && 
    intersection_zmax.x <= max_.x && 
    intersection_zmax.y >= min_.y && 
    intersection_zmax.y <= max_.y && 
    intersection_zmax.z >= min_.z && 
    intersection_zmax.z <= max_.z)
  {
   if(t < tmin)
   {
     tmin = t;
   }
    cut = true;
    
  }

  if (cut == true)
  {
    t = tmin;
    hit.intersectionPoint = r.origin + (t * d);

    glm::vec3 n;
    //test x plane
    if( hit.intersectionPoint.y >= min_.y &&
        hit.intersectionPoint.y <= max_.y &&
        hit.intersectionPoint.z >= min_.z &&
        hit.intersectionPoint.z <= max_.z)
    {
      if (hit.intersectionPoint.x < max_.x)
      {//if hit.intersectionPoint on x-min-plane glm::vec3 n{-1, 0, 0}
        n = glm::normalize(glm::vec3{min_.x, max_.y, max_.z}-max_);
      }
      if (hit.intersectionPoint.x > min_.x)
      { //if hit.intersectionPoint on x-max-plane glm::vec3 n{1, 0, 0}
        n = glm::normalize(max_ - glm::vec3{min_.x, max_.y, max_.z});
      }
    }
    //test y plane
    if( hit.intersectionPoint.x <= max_.x &&
      hit.intersectionPoint.x >= min_.x &&
      hit.intersectionPoint.z <= max_.z &&
      hit.intersectionPoint.z >= min_.z)
    {
      if(hit.intersectionPoint.y < max_.y)
      { //if surfpoint on y-min-plane:
        n = glm::normalize(glm::vec3{max_.x, min_.y, max_.z} - max_);
      }
      if(hit.intersectionPoint.y > min_.y)
      { //if surfpoint on y-max plane
        n = glm::normalize(max_ - glm::vec3{max_.x, min_.y, max_.z});
      }
    }

  //tests z plane
    if (hit.intersectionPoint.x <= max_.x &&
      hit.intersectionPoint.x >= min_.x &&
      hit.intersectionPoint.y <= max_.y &&
      hit.intersectionPoint.y >= min_.y)
    {
      if(hit.intersectionPoint.z < max_.z)
      {
        //if on z min plane:
        n = glm::normalize(glm::vec3{max_.x, max_.y, min_.z} - max_);
      }
      if(hit.intersectionPoint.z > min_.z)
      { //if on z max plane
        n = glm::normalize(max_ - glm::vec3{max_.x, max_.y, min_.z});
      }
    }

    hit.normal = n;
  }

  hit.intersect = cut;
  
  return hit;
}

void Box::translate(glm::vec3 const& direction)
{
  min_ = min_ + direction;
  max_ = max_ + direction;
}

void Box::scale(glm::vec3 const& scale)
{
  max_ = max_ * scale;
}

void Box::rotate(float angle, glm::vec3 const& axis)
{
  glm::vec4 min4{min_, 1};
  glm::vec4 max4{max_, 1};
  glm::vec4 rotatedMin = glm::rotate((angle * (float) (M_PI/180.0f)), axis)
                        * min4;
  glm::vec4 rotatedMax = glm::rotate((angle * (float) (M_PI/180.0f)), axis)
                        * max4;
  glm::vec3 newMin{rotatedMin};
  glm::vec3 newMax{rotatedMax};
  min_ = newMin;
  max_ = newMax;
}