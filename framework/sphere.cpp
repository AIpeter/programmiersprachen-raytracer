#include "sphere.hpp"
#include <cmath>
#include <iostream>

Sphere::Sphere(): // default constructor
  Shape(),
  center_{0, 0, 0},
  radius_{1.0}
  {}

Sphere::Sphere(Sphere const& s):
  Shape(s.name(), s.mat()),
  center_{s.center()},
  radius_{s.radius()}
  {}

Sphere::Sphere(glm::vec3 const& center, float radius,
               std::string const& name, Material const& mat):
  Shape(name, mat),
  center_{center},
  radius_{radius}
  {}

float Sphere::area() const {return (4 * M_PI * radius_ * radius_);}
float Sphere::volume() const
  {return ((4.0/3.0) * M_PI * radius_ * radius_ *radius_);}

glm::vec3 const& Sphere::center() const {return center_;}
float Sphere::radius() const {return radius_;}

/* virtual */ std::ostream& Sphere::print(std::ostream& os) const {
        os << "Sphere " << name() << ", Center (" << center_.x << "," 
                << center_.y << "," << center_.z << "), Radius " << radius_ 
                << "\n" << mat();
        return os;
}

bool Sphere::intersect(Ray const& r, float & d) {
        auto v = glm::normalize(r.direction);
        bool intersect = glm::intersectRaySphere(r.origin, v, center_,
                radius_*radius_, d);
        // std::cout << intersect << "\n";
        return intersect;
}

float Sphere::closer_z() const
{
  return center_.z;
}