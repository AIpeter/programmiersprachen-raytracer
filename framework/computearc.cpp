#include "computearc.hpp"

float computeDiffuseArc(Hit const& hit, Light const& light)
{
  glm::vec3 l_direction = glm::normalize(hit.intersectionPoint - light.getposition());
  float n_length = glm::length(hit.normal);
  float l_length = glm::length(l_direction);
  return (std::max(glm::dot(hit.normal, l_direction), 0.0f)/(n_length * l_length));
}

float computeSpecularArc(Hit const& hit, Ray const& r, Light const& light)
{
  glm::vec3 l_direction = glm::normalize(hit.intersectionPoint - light.getposition());
  glm::vec3 s = glm::normalize((2 * std::max(glm::dot(hit.normal, l_direction), 0.0f))
                * hit.normal - l_direction);
  float specularCos = glm::dot(s, glm::normalize(r.direction));
  float specularArc = glm::acos(specularCos);
  float specularSin = glm::sin(specularArc);
  if(specularSin > 0) 
  {
    return specularCos;
  }
  else 
  {
    return (0 - specularCos);
  }
}