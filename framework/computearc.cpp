#include "computearc.hpp"

float computeDiffuseArc(Hit const& hit, Light const& light)
{
  glm::vec3 l_direction = glm::normalize(light.getposition() - hit.intersectionPoint);
  return std::max(glm::dot(hit.normal, l_direction), 0.0f);
}

float computeSpecularArc(Hit const& hit, Ray const& r, Light const& light)
{ 
  glm::vec3 l_direction = glm::normalize(light.getposition() - hit.intersectionPoint);
  std::cout << "l_direction: " << glm::to_string(l_direction) << "\n";
  glm::vec3 s = glm::reflect(l_direction, glm::normalize(hit.normal));
  std::cout << "s not normalized: " << glm::to_string(s) << "\n";
  s = glm::normalize(s);
  std::cout << "s normalized: " << glm::to_string(s) << "\n";
  auto c = glm::normalize(r.direction);
  std::cout << "c: " << glm::to_string(c) << "\n";
  float specularCos = glm::max(glm::dot(s, c), 0.0f);
  std::cout << "specularCos: " << specularCos << std::endl;
  return specularCos;
}