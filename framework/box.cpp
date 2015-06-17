#include "box.hpp"

Box::Box():
  min_{0, 0, 0},
  max_{1, 1, 1} {}

Box::Box(glm::ve3 const& min, glm::ve3 const& max) :
  min_{min},
  max_{max} {}

float Box::area() const {}
float Box::volume() const {}

glm::vec3 Box::min() const {return min_;}
glm::vec3 Box::max() const {return max_;}