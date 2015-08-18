#include "computearc.hpp"

float computeArc(Sphere const& sphere, float & d, Ray const& r, Light const& light)
{
  glm::vec3 surfacePoint{d*r.direction};
  // std::cout << "SurfacePoint: " << surfacePoint.x << surfacePoint.y << surfacePoint->z << std::endl;
  Ray n{sphere.center(), sphere.center() - surfacePoint}; //Normalenvektor
  Ray l{surfacePoint, surfacePoint - light.getposition()};
  float n_length = glm::length(n.direction);
  float l_length = glm::length(l.direction);
  float arc = glm::acos((glm::dot(n.direction, l.direction))/(n_length*l_length));
  /*
  float deg = (360.0 / (2*M_PI)) * arc;
  std::cout << "Arc: " << deg << "°" << "\n";
  */
  return arc;
}