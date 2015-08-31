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
/*
Hit Box::intersect(Ray const& r, float & t) 
{
  Hit hit;
  glm::vec3 ray_direction_inverted = 1.0f / r.direction;
  float tmin = (min_.x - r.origin.x) * ray_direction_inverted.x;
  float tmax = (max_.x - r.origin.x) * ray_direction_inverted.x;

  if (ray_direction_inverted.x >= 0) 
  {
    tmin = (min_.x - r.origin.x) * ray_direction_inverted.x;
    tmax = (max_.x - r.origin.x) * ray_direction_inverted.x;
  }
  else 
  {
    tmin = (max_.x - r.origin.x) * ray_direction_inverted.x;
    tmax = (min_.x - r.origin.x) * ray_direction_inverted.x;
  } 

  float tymin = (min_.y - r.origin.y) * ray_direction_inverted.y;
  float tymax = (max_.y - r.origin.y) * ray_direction_inverted.y;

  if (ray_direction_inverted.y >= 0) 
  {
    tymin = (min_.y - r.origin.y) * ray_direction_inverted.y;
    tymax = (max_.y - r.origin.y) * ray_direction_inverted.y;
  }
  else 
  {
    tymin = (max_.y - r.origin.y) * ray_direction_inverted.y;
    tymax = (min_.y - r.origin.y) * ray_direction_inverted.y;
  } 

  if ((tmin > tymax) || (tymin > tmax))
  {
    hit.intersect = false;
  }

  if (tymin > tmin)
  {
    tmin = tymin;
  }

  if (tymax < tmax)
  {
    tmax = tymax;
  }

  float tzmin = (min_.z - r.origin.z) * ray_direction_inverted.z;
  float tzmax = (max_.z - r.origin.z) * ray_direction_inverted.z;

  if (ray_direction_inverted.z >= 0) 
  {
    tzmin = (min_.z - r.origin.z) * ray_direction_inverted.z;
    tzmax = (max_.z - r.origin.z) * ray_direction_inverted.z;
  }
  else 
  {
    tzmin = (max_.z - r.origin.z) * ray_direction_inverted.z;
    tzmax = (min_.z - r.origin.z) * ray_direction_inverted.z;
  } 

  if ((tmin > tzmax) || (tzmin > tmax))
  {
    hit.intersect = false;
  }

  if (tzmin > tmin)
  {
    tmin = tzmin;
  }

  if (tzmax < tmax)
  {
    tmax = tzmax;
  }

  hit.intersect = true;

  if (hit.intersect == true)
  {
    hit.intersectionPoint = r.origin + (tmin * r.direction);
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
  std::cout << "normal: " << glm::to_string(hit.normal) << std::endl;
  t = tmin;
  return hit;
}
*/

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

    if((hit.intersectionPoint.x == min_.x) || (hit.intersectionPoint.x == max_.x))
    {
      if(hit.intersectionPoint.x == min_.x)
      {
        n = glm::normalize(glm::vec3{min_.x, max_.y, max_.z}-max_);
      }
      else if(hit.intersectionPoint.x == max_.x)
      {
        n = glm::normalize(max_ - glm::vec3{min_.x, max_.y, max_.z});
      }
    }
    else if((hit.intersectionPoint.y == min_.y) || (hit.intersectionPoint.y == max_.y))
    {
      if(hit.intersectionPoint.y == min_.y)
      {
        n = glm::normalize(glm::vec3{max_.x, min_.y, max_.z} - max_);
      }
      else if(hit.intersectionPoint.y == max_.y)
      {
        n = glm::normalize(max_ - glm::vec3{max_.x, min_.y, max_.z});
      }
    }
    else if((hit.intersectionPoint.z == min_.z) || (hit.intersectionPoint.z == max_.z))
    {
      if(hit.intersectionPoint.z == min_.z)
      {
        n = glm::normalize(glm::vec3{max_.x, max_.y, min_.z} - max_);
      }
      else if(hit.intersectionPoint.z == max_.z)
      {
        n = glm::normalize(max_ - glm::vec3{max_.x, max_.y, min_.z});
      }
    }

    /*
    //test x plane
    if( hit.intersectionPoint.y >= min_.y &&
        hit.intersectionPoint.y <= max_.y &&
        hit.intersectionPoint.z >= min_.z &&
        hit.intersectionPoint.z <= max_.z)
    {
      if (hit.intersectionPoint.x < max_.x)
      {//if hit.intersectionPoint on x-min-plane glm::vec3 n{-1, 0, 0}
        // n = glm::normalize(glm::vec3{min_.x, max_.y, max_.z}-max_);
        n = {-1, 0, 0};
      }
      else if (hit.intersectionPoint.x > min_.x)
      { //if hit.intersectionPoint on x-max-plane glm::vec3 n{1, 0, 0}
        // n = glm::normalize(max_ - glm::vec3{min_.x, max_.y, max_.z});
        n = {1, 0, 0};
      }
    }
    //test y plane
    else if( hit.intersectionPoint.x <= max_.x &&
      hit.intersectionPoint.x >= min_.x &&
      hit.intersectionPoint.z <= max_.z &&
      hit.intersectionPoint.z >= min_.z)
    {
      if(hit.intersectionPoint.y < max_.y)
      { //if surfpoint on y-min-plane:
        // n = glm::normalize(glm::vec3{max_.x, min_.y, max_.z} - max_);
        n = {0, -1, 0};
      }
      else if(hit.intersectionPoint.y > min_.y)
      { //if surfpoint on y-max plane
        // n = glm::normalize(max_ - glm::vec3{max_.x, min_.y, max_.z});
        n = {0, 1, 0};
      }
    }

  //tests z plane
    else if (hit.intersectionPoint.x <= max_.x &&
      hit.intersectionPoint.x >= min_.x &&
      hit.intersectionPoint.y <= max_.y &&
      hit.intersectionPoint.y >= min_.y)
    {
      if(hit.intersectionPoint.z < max_.z)
      {
        //if on z min plane:
        // n = glm::normalize(glm::vec3{max_.x, max_.y, min_.z} - max_);
        n = {0, 0, -1};
      }
      else if(hit.intersectionPoint.z > min_.z)
      { //if on z max plane
        // n = glm::normalize(max_ - glm::vec3{max_.x, max_.y, min_.z});
        n = {0, 0, 1};
      }
    }
    */

    hit.normal = n;
    /*
    std::cout << "intersectionPoint: " << glm::to_string(hit.intersectionPoint) << "\n";
    std::cout << "min_: " << glm::to_string(min_) << "\n";
    std::cout << "max_: " << glm::to_string(max_) << "\n";
    std::cout << "normal: " << glm::to_string(hit.normal) << std::endl;
    */
  }
  // std::cout << "normal: " << glm::to_string(hit.normal) << "\n";
  hit.intersect = cut;
  
  return hit;
}

/*
Hit Box::intersect(Ray const& r, float & t)
{
  Hit hit;
  float tmin = std::numeric_limits<float>::infinity();
  bool cut = false;
  auto v = r.direction;
  if (glm::intersectRayPlane(r.origin, r.direction, min_,
    glm::normalize(glm::vec3{min_.x, max_.y, max_.z}-max_),
    t) == true)
  {
    if(t < tmin)
    {
      //std::cout << "t1 = " << t << std::endl;
      tmin = t;
    }
    cut = true;
  }
  if (glm::intersectRayPlane(r.origin, v, max_,
    glm::normalize(max_ - glm::vec3{min_.x, max_.y, max_.z}),
    t) == true)
  {
    if(t < tmin)
    {
      //std::cout << "t2 = " << t << std::endl;
      tmin = t;
    }
    cut = true;
  }
  if (glm::intersectRayPlane(r.origin, v, min_,
    glm::normalize(glm::vec3{max_.x, min_.y, max_.z} - max_),
    t) == true)
  {
    if(t < tmin)
    {
      //std::cout << "t3 = " << t << std::endl;
      tmin = t;
    }
    cut = true;
  }
  if (glm::intersectRayPlane(r.origin, v, max_,
    glm::normalize(max_ - glm::vec3{max_.x, min_.y, max_.z}),
    t) == true)
  {
    if(t < tmin)
    {
      //std::cout << "t5 = " << t << std::endl;
      tmin = t;
    }
    cut = true;
  }
  if (glm::intersectRayPlane(r.origin, v, min_,
    glm::normalize(glm::vec3{max_.x, max_.y, min_.z} - max_),
    t) == true)
  {
    if(t < tmin)
    {
      //std::cout << "t6 = " << t << std::endl;
      tmin = t;
    }
    cut = true;
  }
  if (glm::intersectRayPlane(r.origin, v, max_,
    glm::normalize(max_ - glm::vec3{max_.x, max_.y, min_.z}),
    t) == true)
  {
    if(t < tmin)
    {
      //std::cout << "t7 = " << t << std::endl;
      tmin = t;
    }
    cut = true;
  }

  if(tmin != std::numeric_limits<float>::infinity())
  {
    //std::cout << "t8 = " << t << std::endl;
    t = tmin;
  }

  if(cut == true)
  {
    t = tmin;
    hit.intersectionPoint = r.origin + (t * r.direction);

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
  std::cout << "normal: " << glm::to_string(hit.normal) << std::endl;
  hit.intersect = cut;
  
  return hit;
}
*/
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