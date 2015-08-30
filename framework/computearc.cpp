#include "computearc.hpp"

float computeDiffuseArc(Hit const& hit, Light const& light)
{
  glm::vec3 l_direction = glm::normalize(hit.intersectionPoint - light.getposition());
  return std::max(glm::dot(hit.normal, l_direction), 0.0f);
}

float computeSpecularArc(Hit const& hit, Ray const& r, Light const& light)
{ 
  glm::vec3 l_direction = glm::normalize(hit.intersectionPoint - light.getposition());
  glm::vec3 s = glm::reflect(l_direction, hit.normal);
  s = glm::normalize(s);
  auto c = glm::normalize(r.direction);
  float specularCos = glm::dot(s, c);
  return specularCos;
}