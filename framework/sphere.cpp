#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
  center_{0, 0, 0},
  radius_{1.0},
  Shape() {}

Sphere::Sphere(std::string const& name):
  center_{0, 0, 0},
  radius_{1.0},
  Shape(name) {}

Sphere::Sphere(Color const& color):
  center_{0, 0, 0},
  radius_{1.0},
  Shape(color) {}

Sphere::Sphere(std::string const& name, Color const& color):
  center_{0, 0, 0},
  radius_{1.0},
  Shape(name, color) {}

Sphere::Sphere(glm::vec3 const& center, float radius):
  center_{center},
  radius_{radius},
  Shape() {}

Sphere::Sphere(glm::vec3 const& center, float radius,
               std::string const& name):
  center_{center},
  radius_{radius},
  Shape(name) {}

Sphere::Sphere(glm::vec3 const& center, float radius,
               Color const& color):
  center_{center},
  radius_{radius}
  Shape(color) {}

Sphere::Sphere(glm::vec3 const& center, float radius,
               std::string const& name, Color const& color):
  center_{center},
  radius_{radius}
  Shape(name, color) {}


float Sphere::area() const {return (4 * M_PI * radius_ * radius_);}
float Sphere::volume() const
  {return ((4.0/3.0) * M_PI * radius_ * radius_ *radius_);}

glm::vec3 Sphere::center() const {return center_;}
float   Sphere::radius() const {return radius_;}