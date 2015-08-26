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

Color Sphere::getLight(float & d, Ray const& r, Light const& light, float shade) const
{
  if(shade == 0) // Schatten
  {
    Color licht = (light.getla()* mat_.ka());
    return licht;
  }
  
  else // kein Schatten
  {
    float diffuseCos = computeDiffuseArc(*this, d, r, light);
    float specularCos = computeSpecularArc(*this, d, r, light);
    Color licht = (light.getld() * mat_.kd() * diffuseCos)
                  + (light.getld() * mat_.ks() * (pow(specularCos, mat_.m())))
                  + (light.getla()* mat_.ka());
    return licht;
  }
}

void Sphere::translate(glm::vec3 const& direction)
{
  center_ = center_ + direction;
}

void Sphere::scale(glm::vec3 const& scale)
{
  radius_ = radius_ * scale.x;
}