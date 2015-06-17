#include "box.hpp"

Box::Box():
  min_{0, 0, 0},
  max_{1, 1, 1},
  name_{},
  color_{0.0, 0.0, 0.0} {}

Box::Box(std::string name):
  min_{0, 0, 0},
  max_{1, 1, 1},
  name_{name},
  color_{0.0, 0.0, 0.0} {}

Box::Box(Color color):
  min_{0, 0, 0},
  max_{1, 1, 1},
  name_{},
  color_{color} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
  min_{min},
  max_{max},
  name_{},
  color_{0.0, 0.0, 0.0} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string name):
  min_{min},
  max_{max},
  name_{name},
  color_{0.0, 0.0, 0.0} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, Color color):
  min_{min},
  max_{max},
  name_{},
  color_{color} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Color color):
  min_{min},
  max_{max},
  name_{name},
  color_{color} {}

float Box::area() const {}
float Box::volume() const {}

glm::vec3 Box::min() const {return min_;}
glm::vec3 Box::max() const {return max_;}