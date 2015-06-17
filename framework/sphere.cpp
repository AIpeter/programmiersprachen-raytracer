#include "sphere.hpp"

Sphere::Sphere() :
    center_{0, 0},
    radius_{1.0} {}

float area() const {}
float volume() const {}

glm::vec3 Sphere::center() const {return center_;}
float   Sphere::radius() const {return radius_;}