#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
  center_{0, 0, 0},
  radius_{1.0},
  name_{},
  color_{0.0, 0.0, 0.0} {}

Sphere::Sphere(std::string name):
  center_{0, 0, 0},
  radius_{1.0},
  name_{name},
  color_{0.0, 0.0, 0.0} {}

Sphere::Sphere(Color color):
  center_{0, 0, 0},
  radius_{1.0},
  name_{},
  color_{color} {}

Sphere::Sphere(std::string name, Color color):
  center_{0, 0, 0},
  radius_{1.0},
  name_{name},
  color_{color} {}

Sphere::Sphere(glm::vec3 const& center, float radius):
  center_{center},
  radius_{radius},
  name_{},
  color_{0.0, 0.0, 0.0} {}

Sphere::Sphere(glm::vec3 const& center, float radius, std::string name):
  center_{center},
  radius_{radius},
  name_{name},
  color_{0.0, 0.0, 0.0} {}

Sphere::Sphere(glm::vec3 const& center, float radius, Color color):
  center_{center},
  radius_{radius},
  name_{},
  color_{color} {}

Sphere::Sphere(glm::vec3 const& center, float radius,
               std::string name, Color color):
  center_{center},
  radius_{radius},
  name_{name},
  color_{color} {}


float Sphere::area() const {return (4 * M_PI * radius_ * radius_);}
float Sphere::volume() const
  {return ((4.0/3.0) * M_PI * radius_ * radius_ *radius_);}

glm::vec3 Sphere::center() const {return center_;}
float   Sphere::radius() const {return radius_;}