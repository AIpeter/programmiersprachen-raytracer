#include "box.hpp"

Box::Box(): // default constructor
  Shape(),
  min_{0, 0, 0},
  max_{1, 1, 1} {}

Box::Box(Box const& b): // copy constructor
  Shape(b.name(), b.mat()),
  min_{b.min_},
  max_{b.max_} {}

Box::Box(std::string const& name, Material const& mat):
  Shape(name, mat),
  min_{0, 0, 0},
  max_{1, 1, 1} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
  Shape(),
  min_{min},
  max_{max} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max,
         std::string const& name, Material const& mat):
  Shape(name, mat),
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
  os << Shape::print(os) << "Minimum: ("
     << min_.x << "," << min_.y << ","<< min_.z << "), Maximum: ("
     << max_.x << "," << max_.y << "," << max_.z << ")" << "\n";
      return os;
}

bool Box::intersect(Ray const& r, float& t)
{
  auto v = glm::normalize(r.direction);
  t = (min_.x - r.origin.x) / v.x;
  glm::vec3 s = r.origin + (t * v);

  if((s.y >= min_.y && s.y <= max_.y)&&
     (s.z >= min_.z && s.z <= max_.z))
  {
    return true;
  }

  else return false;
}