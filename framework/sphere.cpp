#include "sphere.hpp"
#include <cmath>

Sphere::Sphere(): // default constructor
  Shape(),
  center_{0, 0, 0},
  radius_{1.0} {}

Sphere::Sphere(Sphere const& s): // copy constructor
  Shape(s.name(), s.color()),
  center_{s.center_},
  radius_{s.radius_} {}

Sphere::Sphere(std::string const& name):
  Shape(name),
  center_{0, 0, 0},
  radius_{1.0} {}

Sphere::Sphere(Color const& color):
  Shape(color),
  center_{0, 0, 0},
  radius_{1.0} {}

Sphere::Sphere(std::string const& name, Color const& color):
  Shape(name, color),
  center_{0, 0, 0},
  radius_{1.0} {}

Sphere::Sphere(glm::vec3 const& center, float radius):
  Shape(),
  center_{center},
  radius_{radius} {}

Sphere::Sphere(glm::vec3 const& center, float radius,
               std::string const& name):
  Shape(name),
  center_{center},
  radius_{radius} {}

Sphere::Sphere(glm::vec3 const& center, float radius,
               Color const& color):
  Shape(color),
  center_{center},
  radius_{radius} {}

Sphere::Sphere(glm::vec3 const& center, float radius,
               std::string const& name, Color const& color):
  Shape(name, color),
  center_{center},
  radius_{radius} {}


float Sphere::area() const {return (4 * M_PI * radius_ * radius_);}
float Sphere::volume() const
  {return ((4.0/3.0) * M_PI * radius_ * radius_ *radius_);}

glm::vec3 Sphere::center() const {return center_;}
float   Sphere::radius() const {return radius_;}

std::ostream& Sphere::print(std::ostream& os) const
{
  os << "Center: (" << center_.x << ", " << center_.y << ", " << center_.z
     << "), Radius: " << radius_ << "\n";
      return os;
}