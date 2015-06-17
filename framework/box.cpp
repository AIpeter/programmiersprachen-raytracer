#include "box.hpp"

Box::Box():
  min_{0, 0, 0},
  max_{1, 1, 1},
  Shape() {}

Box::Box(std::string const& name):
  min_{0, 0, 0},
  max_{1, 1, 1},
  Shape(name) {}

Box::Box(std::string const& name, Color const& color):
  min_{0, 0, 0},
  max_{1, 1, 1},
  Shape(name, color) {}

Box::Box(Color const& color):
  min_{0, 0, 0},
  max_{1, 1, 1},
  Shape(color) {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
  min_{min},
  max_{max},
  Shape() {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
         std::string const& name):
  min_{min},
  max_{max},
  Shape(name) {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
         Color const& color):
  min_{min},
  max_{max}
  Shape(color) {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
         std::string const& name, Color const& color):
  min_{min},
  max_{max},
  Shape(name, color) {}
  

float Box::area() const {}
float Box::volume() const {}

glm::vec3 Box::min() const {return min_;}
glm::vec3 Box::max() const {return max_;}