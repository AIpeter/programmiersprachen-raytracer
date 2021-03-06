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
        glm::vec4 r_origin_4{r.origin, 1};
        glm::vec4 r_direction_4{r.direction, 0};
        r_origin_4 = world_transformation_inv_ * r_origin_4;
        r_direction_4 = world_transformation_inv_ * r_direction_4;
        Hit hit_;
        hit_.intersect = glm::intersectRaySphere(glm::vec3{r_origin_4},
                          glm::normalize(glm::vec3{r_direction_4}), center_,
                          radius_*radius_, d);
        if (hit_.intersect == true)
        {
          hit_.intersectionPoint = glm::vec3{r_origin_4}
                                    + (d * glm::vec3{r_direction_4});
          hit_.normal = hit_.intersectionPoint - center_;
          glm::vec4 normal_4{hit_.normal, 0};
          normal_4 = glm::transpose(world_transformation_inv_) * normal_4;
          hit_.normal = glm::vec3{normal_4};
          hit_.normal = glm::normalize(hit_.normal);
        }
        return hit_;
}
/*
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
}*/