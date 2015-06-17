#include "sphere.hpp"
#include <cmath>

Sphere::Sphere() :
    center_{0, 0, 0},
    radius_{1.0} {}

float Sphere::area() const {return (4 * M_PI * radius_ * radius_);}
float Sphere::volume() const
  {return ((4.0/3.0) * M_PI * radius_ * radius_ *radius_);}

glm::vec3 Sphere::center() const {return center_;}
float   Sphere::radius() const {return radius_;}