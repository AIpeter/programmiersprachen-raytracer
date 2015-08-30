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

Hit Sphere::intersect(Ray const& r, float & d) {
        auto v = glm::normalize(r.direction);
        Hit hit_;
        hit_.intersect = glm::intersectRaySphere(r.origin, v, center_,
                radius_*radius_, d);
        if (hit_.intersect == true)
        {
          hit_.intersectionPoint = r.origin + (d * r.direction);
          hit_.normal = glm::normalize(hit_.intersectionPoint - center_);
        }
        return hit_;
}

void Sphere::translate(glm::vec3 const& direction)
{
  center_ = center_ + direction;
}

void Sphere::scale(glm::vec3 const& scale)
{
  radius_ = radius_ * scale.x;
}

void Sphere::rotate(float angle, glm::vec3 const& axis)
{
  glm::vec4 c4{center_, 1};
  glm::vec4 rotatedCenter = glm::rotate((angle * (float) (M_PI/180.0f)), axis) * c4;
  glm::vec3 newCenter{rotatedCenter};
  center_ = newCenter;
}