#include "computearc.hpp"

float computeDiffuseArc(Sphere const& sphere, float & d, Ray const& r, Light const& light)
{
  glm::vec3 surfacePoint{d*r.direction};
  // std::cout << "SurfacePoint: " << surfacePoint.x << surfacePoint.y << surfacePoint->z << std::endl;
  Ray n{sphere.center(), sphere.center() - surfacePoint}; //Normalenvektor
  Ray l{surfacePoint, surfacePoint - light.getposition()};
  float n_length = glm::length(n.direction);
  float l_length = glm::length(l.direction);
  float diffuseArc = (std::max(glm::dot(n.direction, l.direction), 0.0f))/(n_length*l_length);
  /*
  float deg = (360.0 / (2*M_PI)) * arc;
  std::cout << "Arc: " << deg << "°" << "\n";
  */
  /*
  if(glm::sin(diffuseArc) >= 0) 
  {
    return glm::cos(diffuseArc);
  }
  else 
  {
    return (0 - glm::cos(diffuseArc));
  }
  */
  return diffuseArc;
}

float computeSpecularArc(Sphere const& sphere, float & d, Ray const& r, Light const& light)
{
  glm::vec3 surfacePoint{d*r.direction};
  Ray n{sphere.center(), glm::normalize(sphere.center() - surfacePoint)}; //Normalenvektor
  Ray l{surfacePoint, glm::normalize(surfacePoint - light.getposition())};
  // glm::vec3 s = glm::reflect(l.direction, n.direction);
  /*
  glm::vec3 s{n.direction.x - l.direction.x + n.direction.x,
              n.direction.y - l.direction.y + n.direction.y,
              n.direction.z - l.direction.z + n.direction.z};
  */
  //glm::vec3 s = (2 * glm::dot(l.direction, n.direction))*n.direction - l.direction;
  glm::vec3 s = (2 * std::max(glm::dot(n.direction, l.direction), 0.0f))*n.direction - l.direction;
  s = glm::normalize(s);
  auto c = glm::normalize(r.direction);
  float specularCos = glm::dot(s, c);
  float specularArc = glm::acos(specularCos);
  float specularSin = glm::sin(specularArc);
  // std::cout << specularArc << std::endl;
  if(specularSin > 0) 
  {
    return specularCos;
  }
  else 
  {
    return (0 - specularCos);
  }
  

  /*
  float n_length = glm::length(n.direction);
  float r_length = glm::length(r.direction);
  // Winkel zwischen cameraRay und Normalenvektor minus Winkel zwischen Lichtquelle und Normalenvektor
  float specularArc = ((glm::dot(n.direction, r.direction))/(n_length*r_length))
                      - (computeDiffuseArc(sphere, d, r, light));
  //specularArc = glm::cos(specularArc);
  */
}

float computeDiffuseArc(Box const& box, float & d, Ray const& r, Light const& light)
{/*
  glm::vec3 surfacePoint{d*r.direction};
  auto diffuseArc = [](glm::vec3 const& surfacePoint, Ray const& r, Light const& light)
  {

  }

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
  /*
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
  /*
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
  /*
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
  /*
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
  /*
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
    }*/
}

float computeSpecularArc(Box const& box, float & d, Ray const& r, Light const& light)
{

}