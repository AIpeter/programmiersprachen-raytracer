#include "box.hpp"

Box::Box(): // default constructor
  Shape(),
  min_{0, 0, 0},
  max_{1, 1, 1} {}

Box::Box(Box const& b): // copy constructor
  Shape(b.name(), b.color()),
  min_{b.min_},
  max_{b.max_} {}


Box::Box(std::string const& name):
  Shape(name),
  min_{0, 0, 0},
  max_{1, 1, 1} {}

Box::Box(Color const& color):
  Shape(color),
  min_{0, 0, 0},
  max_{1, 1, 1} {}

Box::Box(std::string const& name, Color const& color):
  Shape(name, color),
  min_{0, 0, 0},
  max_{1, 1, 1} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
  Shape(),
  min_{min},
  max_{max} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
         std::string const& name):
  Shape(name),
  min_{min},
  max_{max} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
         Color const& color):
  Shape(color),
  min_{min},
  max_{max} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
         std::string const& name, Color const& color):
  Shape(name, color),
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

std::ostream& Box::print(std::ostream& os) const
{
  os << "Name: " << name_ << ", Color: " << color_ << "Minimum: ("
     << min_.x << ", " << min_.y << ", "<< min_.z << "), Maximum: ("
     << max_.x << ", " << max_.y << ", " << max_.z << ")" << "\n";
      return os;
}