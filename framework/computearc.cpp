#include "computearc.hpp"

float computeDiffuseArc(Sphere const& sphere, float & d, Ray const& r, Light const& light)
{
  glm::vec3 surfacePoint{d*r.direction};
  // std::cout << "SurfacePoint: " << surfacePoint.x << surfacePoint.y << surfacePoint->z << std::endl;
  Ray n{sphere.center(), sphere.center() - surfacePoint}; //Normalenvektor
  Ray l{surfacePoint, surfacePoint - light.getposition()};
  float n_length = glm::length(n.direction);
  float l_length = glm::length(l.direction);
  float diffuseArc = (glm::dot(n.direction, l.direction))/(n_length*l_length);
  /*
  float deg = (360.0 / (2*M_PI)) * arc;
  std::cout << "Arc: " << deg << "°" << "\n";
  */
  return diffuseArc;
}

float computeSpecularArc(Sphere const& sphere, float & d, Ray const& r, Light const& light)
{
  glm::vec3 surfacePoint{d*r.direction};
  Ray n{sphere.center(), glm::normalize(sphere.center() - surfacePoint)}; //Normalenvektor
  Ray l{surfacePoint, glm::normalize(surfacePoint - light.getposition())};
  glm::vec3 s{n.direction.x - l.direction.x + n.direction.x,
              n.direction.y - l.direction.y + n.direction.y,
              n.direction.z - l.direction.z + n.direction.z};
  s = glm::normalize(s);
  auto c = glm::normalize(r.direction);
  float specularArc = glm::dot(s, c);

  /*
  float n_length = glm::length(n.direction);
  float r_length = glm::length(r.direction);
  // Winkel zwischen cameraRay und Normalenvektor minus Winkel zwischen Lichtquelle und Normalenvektor
  float specularArc = glm::acos((glm::dot(n.direction, r.direction))/(n_length*r_length))
                      - glm::acos(computeDiffuseArc(sphere, d, r, light));
  specularArc = glm::cos(specularArc);
  */
  return specularArc;
}