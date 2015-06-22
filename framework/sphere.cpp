#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
  Shape(),
  center_{0, 0, 0},
  radius_{1.0} {}

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